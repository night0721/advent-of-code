games = []
with open('input') as f:
    for line in f:
        splitted = linerstrip().split(":")
        id = splitted[0].split(" ")[1]
        sets = "".join(splitted[1]).split(";")
        maxes = [0, 0, 0]
        for i in sets:
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
                if colors[0] > maxes[0]:
                    maxes[0] = colors[0]
                if colors[1] > maxes[1]:
                    maxes[1] = colors[1]
                if colors[2] > maxes[2]:
                    maxes[2] = colors[2]
        games.append(maxes[0] * maxes[1] * maxes[2])
print(sum(games))
