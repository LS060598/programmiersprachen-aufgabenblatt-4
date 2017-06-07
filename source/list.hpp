#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>
#include <utility>



template<typename T>
struct List;

template<typename T>
struct ListNode
{
    ListNode() : m_value(), m_prev(nullptr), m_next(nullptr) {}
    ListNode(T const& v, ListNode* prev, ListNode* next)
        : m_value(v), m_prev(prev), m_next(next)
    {}
    T m_value;
    ListNode* m_prev; 
    ListNode* m_next;
};


template<typename T>
struct ListIterator
{
typedef ListIterator<T> Self;

  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

  friend class List<T>;
  // not implemented yet
  

  // Aufgabe 4.5

  ListIterator() : m_node {nullptr} {}
  ListIterator(ListNode<T>* n) : m_node {n} {}

  reference operator * () const {
    return m_node -> m_value; //m_node zeigt auf m_value
  }


  pointer operator -> () const { //(*a).b gleiche wie Pfeil // a zeigt auf b (structure dereference)
    return &(m_node -> m_value); // adresse-of()
  } 


  Self& operator ++ () { // increment prefix a++(R& K::operator ++() )
    if (m_node) {
      m_node = m_node -> m_next; // m_node zeigt jetzt auf nächsten knoten
    }
    return *this; // gibt m_node zurück
  }


  Self operator ++ (int) { // increment postfix ++a (R K::operator ++(int))
    Self temp = *this; // Kopie
    ++(*this); // pre-increment 
    return temp; // gibt die Kopie vor increment zurück 
  } 


  bool operator == (const Self& x) const { // schaut ob knoten gleich (iterator zeigt / knoten von x)
    return m_node == x.m_node;
  } 


  bool operator != (const Self& x) const { // schaut ob knoten  nicht gleich (iterator zeigt / knoten von x)
     return m_node != x.m_node;
  }


  Self next() const{
    if(m_node)
      return ListIterator(m_node->m_next);
    else
      return ListIterator(nullptr);
  }

  Self prev() const { // hinzugefügt für Aufgabe 4.9 (Einfügen vor einer Stelle)
    if (m_node)
      return ListIterator(m_node->m_prev);
    else
      return ListIterator();
}



private:
// the node the iterator is pointing to
    ListNode<T>* m_node = nullptr;
};

template<typename T>
struct ListConstIterator
{
    friend class List<T>;
  

public:
//not implemented yet
private:
    ListNode<T>* m_node = nullptr;
};
 

template <typename T>
class List
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef ListIterator<T> iterator;
    typedef ListConstIterator<T> const_iterator;

    friend class ListIterator<T>;
    friend class ListConstIterator <T>;
    // not implemented yet


// Aufgabe 4.2

//Default constructor
List(): m_size {0}, m_first {nullptr}, m_last {nullptr} {} 

    
  bool empty() const {
    return m_size == 0; // schaut ob liste leer oder nicht
  }

    // Größe der liste
  std::size_t size() const {
    return m_size;
}




//Aufgabe 4.3


//Fügt ein neues Element an den Anfang
  void push_front(T const& a) {
    if (m_size == 0) { //wenn liste leer
      m_first = new ListNode<T>{a, nullptr, nullptr};
      m_last = m_first;
    }

    else if (m_size >= 1) { // wenn schon was drin
      m_first = new ListNode<T>{a, nullptr, m_first};
      m_first -> m_next -> m_prev = m_first;
    }

    ++m_size;
}



// Entfernen des ersten Elements der Liste
  void pop_front() {
    if (m_size == 1) {
      assert(m_first != nullptr);
      delete m_first;
      m_first = nullptr;
      m_size = 0;
    }

    else if (m_size > 1) {
      assert(m_first != nullptr);
      delete m_first;
      m_first = m_first -> m_next;
      --m_size;
    }
}




// Hinzufügen einses Elementes ans Ende der Liste
  void push_back(T const& a) {
    if (m_size == 0) {
      m_last = new ListNode<T>{a, nullptr, nullptr};
      m_first = m_last;
    }

    else if (m_size >= 1) {
      m_last = new ListNode<T>{a, m_last, nullptr};
      m_last -> m_prev -> m_next = m_last;
    }

    ++m_size;
}


// Letztes Element löschen
  void pop_back() {
    if (m_size == 1) {
      assert(m_last != nullptr);
      delete m_last;
      m_last = nullptr;
      m_size = 0;
    }

    else if (m_size > 1) {
      assert(m_last != nullptr);
      delete m_last;
      m_last = m_last -> m_prev;
      --m_size;
    }
  }
  
//erstes element
    T& front(){
    	return m_first->m_value;
    }
//letztes element
    T& back(){
    	return m_last->m_value;
    }




//Aufgabe 4.4

// destructor 
  ~List() {
    clear(); 
  }

// Löscht alle elemente aus liste
  void clear() {
    while (m_size > 0) {
      pop_front();
    }
}


//Aufgabe 4.6

  iterator begin() const { // iterator zeigt auf m_first
  	return iterator(m_first);
}

  iterator end() const { // iterator zeigt auf element nach m_last
  	return iterator();
}






//Aufgabe 4.8 copy-constructor

// Der Compiler erstellt einen copy-constructor, wenn man selber keinen erstellt.
//Anders zum default-constructor, ist die vom Compiler body erstellte Kopie nicht leer
//Es werden alle data members der übergebenden Objekte in das neu erstellte Objekt kopiert
//Wenn man an der Liste aber etwas verändert, verändert sich auch die Kopie
//Wenn man etwas anfügt, wird dies jedoch nicht zusätzlich in der Kopie angefügt,
//da der Zeiger schon vorher auf das letzte Element zeigt
//flache Kopie

List(List<T> const& x): m_size {0}, m_first {nullptr}, m_last {nullptr} {
    for (iterator i = x.begin(); i != x.end(); ++i) {
      push_back(*i); // tip: push_* Methode
    }
}


//Augabe 4.9
//Einfügen von Objekt
  void insert(iterator pos, T const& value) {
    if (pos == begin()) { // wenn am anfang
      push_front(value);
    }
    else if (pos == end()) { // wenn am ende
      push_back(value);
    }
    else {// sonst
      ListNode <T>* insertNode = new ListNode<T> {value, pos.prev().m_node, pos.m_node};

      pos.prev().m_node -> m_next = insertNode;
      pos.m_node -> m_prev = insertNode;
      ++m_size; // zählt größe hoch
    }
}



//Aufgabe 4.10
//Teil 1 normal(memberfunktion)
//Reihenfolge umkehren


  void reverse() {
    List<T> tmp{*this}; // Liste wird kopiert
    clear(); // inhalt gelöscht
    for (iterator it = tmp.begin(); it != tmp.end(); ++it) {
      push_front(*it); // durch tmp durch iteriert und umgekehrte reihen folge mit push_front in initialisierte liste
    }
}


//Aufgabe4.13

List(List&& ml): m_size {ml.m_size}, m_first {ml.m_first}, m_last {ml.m_last} { // stielt die elemente von ml
    ml.m_size = 0;
    ml.m_first = nullptr;
    ml.m_last = nullptr; // lm ist jetzt leer
}



private:
    std::size_t m_size = 0;
    ListNode<T>* m_first = nullptr;
    ListNode<T>* m_last = nullptr;
};

//Aufgabe 4.7

template<typename T>
bool operator == (List<T> const& xs, List<T> const& ys) {
  bool result = true;

	if (xs.size() != ys.size()) { // größe von beiden müssen gleich sein um komplett gleich zu sein
		result = false;
	}

	else {
		ListIterator<T> xs_it = xs.begin(); 
		ListIterator<T> ys_it = ys.begin();

		while (xs_it != xs.end() && ys_it != ys.end()) { // anfang bis ende
			if (*xs_it != *ys_it) { // schaut ob elemente an selber position nicht gleich sind
				result = false;
        break;
			}

			++xs_it; // iterator geht ein knoten weiter
			++ys_it;
		}
	}

return result;
}


template<typename T>
bool operator != (List<T> const& xs, List<T> const& ys) { // schaut ob listen ungleich
	return !(xs == ys);
}



//Aufgabe4.10
//Teil 2 freie Funktion
 // Reihenfolge umkehren

template<typename T>
List<T> reverse (List<T> liste) {
  liste.reverse();
  return liste; 
}



#endif // define BUW_LIST_HPP