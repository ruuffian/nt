public class Node<T> {
    private Node<T> next;
    private T data;

    public Node(T d) {
        this.data = d;
        this.next = null;
    }

    public Node(T d, Node<T> n) {
        this.data = d;
        this.next = n;
    }

    public T getData() {
        return this.data;
    }

    public Node<T> getNext() {
        return this.next;
    }

    public void setData(T d) {
        this.data = d;
    }

    public void setNext(Node<T> n) {
        this.next = n;
    }
}
