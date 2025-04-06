import sqlite3
import json
import google.generativeai as genai
import os
import sys

# Configure Gemini API
genai.configure(api_key="AIzaSyCQQKLp1V2GEgnHEab1fKKL6K6O5lcBXZY")

# Load the Gemini model
model = genai.GenerativeModel("gemini-1.5-pro")

def get_matching_traject_ids(search_id):
    try:
        current_dir = os.path.dirname(os.path.abspath(__file__))
        db_path = os.path.join(current_dir, '..', 'DataBase', 'AppCovoiturage.db')

        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()

        # Get search request from DB
        cursor.execute("SELECT depart, destination, seats, price_limit, date_time FROM search_history WHERE id = ?", (search_id,))
        row = cursor.fetchone()

        if not row:
            return json.dumps([])  # Return empty list in JSON format if no results found

        search_input = {
            "depart": row[0],
            "destination": row[1],
            "seats": row[2],
            "price_limit": row[3],
            "date": row[4].split("T")[0] if "T" in row[4] else row[4].split(" ")[0]
        }

        cursor.execute(""" 
            SELECT id, depart, destination, date_time, available_seats, price
            FROM trajects 
            WHERE status = 'pending'
            LIMIT 500
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

        prompt = f"""
                    You are a smart assistant for a carpooling app. Your job is to match a user's search with the best available carpooling trajects and return the IDs of the matching trajects as a JSON array.
                    
                    ### Search request:
                    {json.dumps(search_input, indent=2)}
                    
                    ### Available trajects:
                    {json.dumps(trajects, indent=2)}
                    
                    ### Matching rules:
                    - Prefer exact matches on 'depart', 'destination', and 'date'.
                    - Consider available_seats and price_limit as constraints.
                    - If there is **no exact match**, return **-1 as the first element**, followed by the most similar options.
                    - If exact matches exist, include it first and also include other similar suggestion.
                    - Return at least 10 results.
                    - Return the result as a **valid JSON array** with the traject IDs (for example: `[1, 2, 3]`).
                    """

        response = model.generate_content(prompt)
        output = response.text.strip()

        # Check if output is valid and clean it
        output_cleaned = output.replace("```json", "").replace("```", "").strip()

        if not output_cleaned:
            raise ValueError("Output is empty or invalid")

        traject_ids = json.loads(output_cleaned)  # Parse the cleaned output into JSON
        return json.dumps(traject_ids)  # Return the list of IDs in JSON format

    except json.JSONDecodeError as e:
        return json.dumps([])  # Return empty list if the JSON is invalid

    except Exception as e:
        return json.dumps([])  # Return empty list in case of error

    finally:
        conn.close()

# Main execution
if __name__ == "__main__":
    if len(sys.argv) > 1:
        search_id = int(sys.argv[1])
        result = get_matching_traject_ids(search_id)
        print(result)
    else:
        print("No search ID provided.")
