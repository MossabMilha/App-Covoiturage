import sqlite3
import json
import google.generativeai as genai

# 🔑 Configure Gemini API
genai.configure(api_key="AIzaSyCQQKLp1V2GEgnHEab1fKKL6K6O5lcBXZY")  # Replace with your key

# 🧠 Load the Gemini model
model = genai.GenerativeModel("gemini-1.5-pro")

# 🔍 Main function
def get_matching_traject_ids(search_id):
    try:
        conn = sqlite3.connect('../DataBase/AppCovoiturage.db')
        cursor = conn.cursor()

        # 🎯 Get the search request from DB
        cursor.execute("SELECT depart, destination, seats, price_limit, date_time FROM search_history WHERE id = ?", (search_id,))
        row = cursor.fetchone()

        if not row:
            print("❌ No search found with this ID.")
            return []

        search_input = {
            "depart": row[0],
            "destination": row[1],
            "seats": row[2],
            "price_limit": row[3],
            "date": row[4].split("T")[0] if "T" in row[4] else row[4].split(" ")[0]
        }

        # 🚗 Get trajects from DB (excluding canceled)
        cursor.execute("""
                    SELECT id, depart, destination, date_time, available_seats, price 
                    FROM trajects 
                    WHERE status = 'pending'
                """)
        raw_trajects = cursor.fetchall()

        trajects = [
            {
                "id": t[0],
                "depart": t[1],
                "destination": t[2],
                "date": t[3].split("T")[0] if "T" in t[3] else t[3].split(" ")[0],
                "available_seats": t[4],
                "price": t[5]
            }
            for t in raw_trajects
        ]

        # 📤 Prompt Gemini
        prompt = f"""
You are a smart assistant for a carpooling app. Your job is to match a user's search with the best available carpooling trajects.

### Search request:
{json.dumps(search_input, indent=2)}

### Available trajects:
{json.dumps(trajects, indent=2)}

### Matching rules:
- Prefer exact matches on 'depart', 'destination', and 'date'.
- Consider available_seats and price_limit as constraints.
- If there is **no exact match**, return **-1 as the first element**, followed by the most similar options.
- If exact matches exist, include them first, followed by the most similar suggestions.
- Return at most 10 results in total.
- Do not explain anything, just return a **valid JSON array** of IDs.

### Output format:
Just return a JSON array of traject IDs sorted from most relevant to least.  
Example with matches: [4, 7, 3]  
Example with no exact match: [-1, 8, 5, 12]
"""

        # ✨ Generate response
        response = model.generate_content(prompt)
        output = response.text.strip()

        # 🧹 Clean and parse
        output_cleaned = output.replace("```json", "").replace("```", "").strip()
        traject_ids = json.loads(output_cleaned)

        print("✅ Matching traject IDs:", traject_ids)
        return traject_ids

    except Exception as e:
        print("🔥 Error:", e)
        return []

    finally:
        conn.close()

# 🧪 Example usage
if __name__ == "__main__":
    search_id = 1  # Replace with the search ID you want
    result = get_matching_traject_ids(search_id)
