games = []
with open('input') as f:
    for line in f:
        splitted = line.rstrip().split(":")
        id = splitted[0].split(" ")[1]
        sets = "".join(splitted[1]).split(";")
        for i in sets:
            ok = True
            colors = [0, 0, 0]
            detail = i.strip().split(", ")
            for i in range(len(detail)):
                count = "".join(detail[i]).split(" ")[0]
                color = "".join(detail[i]).split(" ")[1]
                if color == "red":
                    colors[0] += int(count)
                elif color == "green":
                    colors[1] += int(count)
                elif color == "blue":
                    colors[2] += int(count)
            if colors[0] > 12 or colors[1] > 13 or colors[2] > 14:
                ok = False
                break
        if ok:
            games.append(int(id))
    print(sum(games))
