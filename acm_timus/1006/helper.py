with open("aux.in", mode="r", encoding="KOI8-R") as myfile:
    data = myfile.read()
    
    b = bytes(data,"KOI8-R")
    data_encoding = str(b,"cp1251")
    
    print(data_encoding)
