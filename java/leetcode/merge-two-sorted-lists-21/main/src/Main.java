public class Main {
    public static void main(String args[]) {
        ListNode d = new ListNode(4);
        ListNode c = new ListNode(3, d);
        ListNode b = new ListNode(2, c);
        ListNode a = new ListNode(1, b);

        ListNode three = new ListNode(3);
        ListNode two = new ListNode(2, three);
        ListNode one = new ListNode(1, two);

        System.out.println("List 1:");
        printList(a);
        System.out.println("List 2:");
        printList(one);
        System.out.println("Sorted:");
        ListNode sorted = mergeTwoLists(one, a);
        printList(sorted);
    }

    private static void printList(ListNode head) {
        if (head == null) return;
        System.out.print(head.val);
        head = head.next;
        while (head != null) {
            System.out.print(" -> " + head.val);
            head = head.next;
        }
        System.out.println();
    }

    public static ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        ListNode head = new ListNode();
        ListNode cur = head;
        while (list1 != null && list2 != null) {
            if (list1.val < list2.val) {
                cur.next = new ListNode(list1.val);
                list1 = list1.next;
            } else {
                cur.next = new ListNode(list2.val);
                list2 = list2.next;
            }
            cur = cur.next;
        }
        while (list1 != null) {
            cur.next = new ListNode(list1.val);
            list1 = list1.next;
            cur = cur.next;
        }
        while (list2 != null) {
            cur.next = new ListNode(list2.val);
            list2 = list2.next;
            cur = cur.next;
        }
        return head.next;
    }
}
