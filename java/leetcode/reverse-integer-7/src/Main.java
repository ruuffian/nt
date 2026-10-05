import java.util.Arrays;

public class Main {
    static char[] SIGNED_INT_UPPER_BOUND = new char[]{'2', '1', '4', '7', '4', '8', '3', '6', '4', '7'};
    static char[] SIGNED_INT_LOWER_BOUND = new char[]{'2', '1', '4', '7', '4', '8', '3', '6', '4', '8'};

    public static void main(String[] args) {
        int x = -123;
        char[] ray = extractChars(x);
        char[] reversed = reverse(ray);
        int y = parseChars(x, reversed);
        System.out.println(x + " -> " + y);
    }

    public static char[] extractChars(int x) {
        char[] chars = Integer.toString(x).toCharArray();
        if (x < 0) {
            char[] trimmed = new char[chars.length - 1];
            for (int i = 1; i < chars.length; i++) trimmed[i - 1] = chars[i];
            chars = trimmed;
        }
        return chars;
    }

    public static char[] reverse(char[] ray) {
        char[] reversed = new char[ray.length];
        int i = 0;
        int j = ray.length - 1;
        while (i < ray.length) {
            reversed[i] = ray[j];
            i++;
            j--;
        }
        return reversed;
    }

    public static int parseChars(int x, char[] ray) {
        if (!checkBounds(ray, x < 0)) return 0;
        else return Integer.parseInt(String.valueOf(ray)) * sign(x);
    }

    private static int sign(int x) {
        if (x < 0) return -1;
        return 1;
    }

    /* Check if the array of characters resolves to an integer outside 32-bit range. */
    private static boolean checkBounds(char[] ray, boolean negative) {
        try {
            char[] chars = leftPadBound(ray);
            if (negative) {
                for (int i = 0; i < chars.length; i++) {
                    if (chars[i] > SIGNED_INT_LOWER_BOUND[i]) return false;
                    else if (chars[i] < SIGNED_INT_LOWER_BOUND[i]) return true;
                    // If chars[i] == lowerBound[i], check next digit.
                }
                // Reaching here implies chars == lowerBound, so we exit the 'if'.
            } else {
                for (int i = 0; i < chars.length; i++) {
                    if (chars[i] < SIGNED_INT_UPPER_BOUND[i]) return true;
                    else if (chars[i] > SIGNED_INT_UPPER_BOUND[i]) return false;
                    // If chars[i] == upperBound[i], check next digit.
                }
                // Reaching here implies chars == upperBound, so we exit the 'if'.
            }
            return true;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static char[] leftPadBound(char[] ray) throws Exception {
        if (ray.length > SIGNED_INT_UPPER_BOUND.length) {
            throw new RuntimeException("Array length exceeds maximum.");
        }
        char[] out = new char[SIGNED_INT_UPPER_BOUND.length];
        Arrays.fill(out, '0');
        int i = 0;
        int j = out.length - ray.length;
        while (i < ray.length) {
            out[j] = ray[i];
            i++;
            j++;
        }
        return out;
    }
}
