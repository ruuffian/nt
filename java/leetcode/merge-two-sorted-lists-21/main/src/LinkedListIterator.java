import java.util.Iterator;

public class LinkedListIterator<T> implements Iterator<T> {

    private Node<T> cursor;

    public LinkedListIterator(LinkedList<T> l) {
        this.cursor = l.getHead();
    }

    @Override
    public boolean hasNext() {
        return cursor.getNext() != null;
    }

    @Override
    public T next() {
        Node<T> tmp = cursor;
        cursor = cursor.getNext();
        return tmp.getData();
    }
}
