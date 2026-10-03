public class Main {
    static char[] SIGNED_INT_UPPER_BOUND = new char[]{'2', '1', '4', '7', '4', '8', '3', '6', '4', '7'};
    static char[] SIGNED_INT_LOWER_BOUND = new char[]{'-', '2', '1', '4', '7', '4', '8', '3', '6', '4', '8'};

    public static void main(String args[]) {
        int x = 123;
        int y = reverse(x);
        System.out.println(x + " -> " + y);
    }

    public static int reverse(int x) {
        char[] chars = Integer.toString(x).toCharArray();
        char[] reversed = new char[chars.length];
        int i = 0;
        int j = chars.length - 1;
        while (i < chars.length) {
            reversed[i] = chars[j];
            i++;
            j--;
        }
        if (!checkBoundsNaive(Integer.parseInt(String.valueOf(reversed)))) return 0;
        return Integer.parseInt(String.valueOf(reversed));
    }

    private static boolean checkBoundsNaive(int x) {
        return x <= Integer.parseInt(String.valueOf(SIGNED_INT_UPPER_BOUND)) && x >= Integer.parseInt(String.valueOf(SIGNED_INT_LOWER_BOUND));
    }

    /* Check if the array of characters resolves to an integer outside 32-bit range.
    private boolean checkBounds(char[] ray, boolean negative) {
        if (negative) {
            return
        } else {

        }
    }
     */
}
