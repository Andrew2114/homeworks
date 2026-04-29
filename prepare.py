import csv

with open("airport-codes.csv", encoding="utf-8") as fin, \
     open("airports.txt", "w", encoding="utf-8") as fout:
    reader = csv.DictReader(fin)
    count = 0
    for row in reader:
        code = row["iata_code"].strip()
        name = row["name"].strip()
        if code:
            fout.write(f"{code}:{name}\n")
            count += 1
    
    print(f"Создано {count} записей в файле airports.txt")
