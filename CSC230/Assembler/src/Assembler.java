import java.util.ArrayList;
import java.util.Scanner;

public class Assembler {
    public static ArrayList<Integer> machLang = new ArrayList<Integer>();
    public static void main(String[] args) {
        Scanner scr = new Scanner(System.in);
        System.out.println("Assembler - E.Nicholson\n*** Begin entering Assembler:");
        String command = scr.nextLine().toUpperCase();
;
        while(!command.contentEquals("HALT")){
            Scanner scr2 = new Scanner(command);
            String statement = scr2.next();
            char iType = ' ';
            byte op = 0;
            byte rs = 0;
            byte rt = 0;
            byte rd = 0;
            byte shamt = 0;
            byte funct = 0;
            short immediate = 0;

            switch (statement){
                case "ADD":
                    iType = 'R'; shamt = 0; funct = 32;

                    rd = regToByte(scr2.next());
                    rs = regToByte(scr2.next());
                    rt = regToByte(scr2.next());
                    break;
                case "AND":
                    iType = 'R'; shamt = 0; funct = 36;

                    rd = regToByte(scr2.next());
                    rs = regToByte(scr2.next());
                    rt = regToByte(scr2.next());
                    break;
                case "SRL":
                    iType = 'R'; rs = 0; funct = 2;

                    rd = regToByte(scr2.next());
                    rt = regToByte(scr2.next());
                    shamt = scr2.nextByte();
                    break;
                case "SLL":
                    iType = 'R'; rs = 0; funct = 0;

                    rd = regToByte(scr2.next());
                    rt = regToByte(scr2.next());
                    shamt = scr2.nextByte();
                    break;
                case "ADDI":
                    iType = 'I'; op = 8;

                    rt = regToByte(scr2.next());
                    rs = regToByte(scr2.next());
                    immediate = scr2.nextShort();
                    break;
                case "ANDI":
                    iType = 'I'; op = 12;

                    rt = regToByte(scr2.next());
                    rs = regToByte(scr2.next());
                    immediate = scr2.nextShort();
                    break;
                case "BEQ":
                    iType = 'I'; op = 4;

                    rs = regToByte(scr2.next());
                    rt = regToByte(scr2.next());
                    immediate = scr2.nextShort();
                    break;
                case "LW":
                    iType = 'I'; op = 35;

                    rt = regToByte(scr2.next());
                    immediate = scr2.nextShort();
                    rs = regToByte(scr2.next());
                    break;
                case "SW":
                    iType = 'I'; op = 43;

                    rt = regToByte(scr2.next());
                    immediate = scr2.nextShort();
                    rs = regToByte(scr2.next());
            }

            if(iType == 'I'){
                machLang.add(makeI(op, rs, rt, immediate));
            } else {
                machLang.add(makeR(op, rs, rt, rd, shamt, funct));
            }
            command = scr.nextLine().toUpperCase();
        }
        printCode();
    }

    private static void printCode() {
        for(int i = 0; i < machLang.size(); i++){
            System.out.println("***: " + String.format("%32s", Integer.toBinaryString(machLang.get(i))).replace(" ", "0"));
        }
        System.out.println("*** Assembly complete. Program required "+machLang.size()+" words of memory.");
    }

    private static int makeI(byte op, byte rs, byte rt, short immediate) {
        int ret = 0;
        ret = ret + op;
        ret <<= 5;
        ret = ret + rs;
        ret <<= 5;
        ret = ret + rt;
        ret <<= 16;
        ret |= immediate & 0xFFFF;
        return ret;
    }

    private static int makeR(byte op, byte rs, byte rt, byte rd, byte shamt, byte funct) {
        int ret = 0;
        ret = ret + op;
        ret <<= 5;
        ret = ret + rs;
        ret <<= 5;
        ret = ret + rt;
        ret <<= 5;
        ret = ret + rd;
        ret <<= 5;
        ret = ret + shamt;
        ret <<= 6;
        ret = ret + funct;
        return ret;
    }

    private static byte regToByte(String next) {
        byte b = 0;
        char c = next.charAt(1);
        int i = 0;
        if(c != 'Z'){
            i = next.charAt(2);
            b = (byte) (i - 48);
        } else {
            return 0;
        }
        switch (c){
            case 'V':
                b = (byte) (b + 2);
                break;
            case 'A':
                b = (byte) (b + 4);
                break;
            case 'T':
                if(b <= 7){
                    b = (byte) (b + 8);
                } else {
                    b = (byte) (b + 16);
                }
                break;
            case 'S':
                b = (byte) (b + 16);
                break;
        }
        return b;
    }
}