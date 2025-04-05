import sqlite3
import random
from datetime import datetime, timedelta

# --- Data Lists ---
cities = [
    "Amsterdam", "Athens", "Belgrade", "Berlin", "Bratislava", "Brussels", "Bucharest", "Budapest", "Chisinau", "Copenhagen",
    "Dublin", "Helsinki", "Kiev", "Lisbon", "Ljubljana", "London", "Luxembourg", "Madrid", "Malta", "Minsk", "Monaco",
    "Moscow", "Oslo", "Paris", "Podgorica", "Prague", "Reykjavik", "Riga", "Rome", "Sarajevo", "Skopje", "Sofia", "Stockholm",
    "Tallinn", "Tirana", "Valletta", "Vienna", "Vilnius", "Warsaw", "Zagreb"
]

car_models = ["Toyota", "BMW", "Peugeot", "Renault", "Audi", "Mercedes", "Opel", "Skoda"]
statuses = ["pending", "confirmed", "completed", "canceled"]

# --- Connect to SQLite ---
conn = sqlite3.connect('../DataBase/AppCovoiturage.db')  # Adjust path if needed
cursor = conn.cursor()

# --- Random DateTime Generator (within next 7 days) ---
def random_datetime_next_week():
    now = datetime.now()
    max_date = now + timedelta(days=7)
    random_days = random.randint(0, 6)
    random_seconds = random.randint(0, 86399)  # Seconds in a day
    future_datetime = now + timedelta(days=random_days, seconds=random_seconds)
    return future_datetime.strftime("%Y-%m-%d %H:%M:%S")

# --- Generate and Insert Data ---
for _ in range(1000):  # Generate 1000 rows
    depart, destination = random.sample(cities, 2)
    driver_id = 2  # Fixed driver_id
    available_seats = random.randint(1, 4)
    price = round(random.uniform(5.0, 100.0), 2)
    car_model = random.choice(car_models)
    status = random.choice(statuses)
    date_time = random_datetime_next_week()

    cursor.execute("""
        INSERT INTO trajects (driver_id, depart, destination, date_time, available_seats, price, car_model, status, created_at)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, datetime('now'))
    """, (driver_id, depart, destination, date_time, available_seats, price, car_model, status))

# --- Commit and Close ---
conn.commit()
conn.close()
