from random import randint


def lines_parser():
    with open("data.dat", "r", encoding="UTF-8") as file:
        rand_num = randint(0, 99)
        lines = file.readlines()
        return lines[rand_num].strip()
