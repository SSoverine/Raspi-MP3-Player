from RPLCD.i2c import CharLCD
import sys

lcd = CharLCD(i2c_expander = "PCF8574", address=0x27, port=1, cols=16, rows=2, dotsize=8)

def clear():
    #lcd = CharLCD(i2c_expander = "PCF8574", address=0x27, port=1, cols=16, rows=2, dotsize=8)
    lcd.clear()

def write(text, satir):
    #lcd = CharLCD(i2c_expander = "PCF8574", address=0x27, port=1, cols=16, rows=2, dotsize=8)
    lcd.cursor_pos = (satir, 0)
    lcd.write_string(text)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        if sys.argv[1] == "-write" and len(sys.argv)>2:
            text = sys.argv[2]

            if "|" in text:
                write(text.split("|")[1], 1)
                text = text.split("|")[0]

            write(text, 0)
        elif sys.argv[1] == "-clear":
            clear()
