# To be uploaded to https://gavinford.net/cw

from random import randint

FILE_NAME = "cw_training.txt"

def main():
    out = ""
    for _ in range(50):
        for _ in range(5):
            out += str(randint(0,9))
        out += " "
    with open(FILE_NAME, "w") as f:
        f.write(out)

if __name__ == "__main__":
    main()