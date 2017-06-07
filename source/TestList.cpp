#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include <algorithm>
#include "list.hpp"

//Aufgabe 4.2

TEST_CASE("Überprüfung ob Liste leer", "[aufgabe4.2]") {
  List<int> l1 {};
  REQUIRE(l1.empty() == true);
}

TEST_CASE("Größe der Liste", "[aufgabe4.2]") {
  List<int> l1 {};
  REQUIRE(l1.size() == 0);
}




// Aufgabe 4.3
TEST_CASE("add an element with push_front", "[aufgabe4.3]") {
  List<int> list; 
  list.push_front(42); 
REQUIRE(42 == list.front() );

List<int> l2;
  l2.push_front(42);
  l2.push_front(13);
  l2.push_front(4);
REQUIRE(4 == l2.front());
}


TEST_CASE("add an element with push_back", "[aufgabe4.3]") {
  List<int> list {}; 
  list.push_back(42); 
  REQUIRE(42 == list.back());

  List<int> l2 {};
  l2.push_back(4);
  l2.push_back(13);
  l2.push_back(42);
REQUIRE(42 == l2.back());
}


TEST_CASE("remove first element with pop_front", "[aufgabe4.3]") {
  List<int> list {}; 
  list.push_back(42); 
  list.pop_front();
  REQUIRE(true == list.empty());

  List<int> l1 {};
  l1.push_back(42);
  l1.push_back(14);
  l1.pop_front();
REQUIRE(14 == l1.front());
}


TEST_CASE("remove last element with pop_back", "[aufgabe4.3]") {
  List<int> list {}; 
  list.push_back(42); 
  list.pop_back();
  REQUIRE(true == list.empty());

  List<int> l1 {};
  l1.push_back(42);
  l1.push_back(14);
  l1.pop_back();
  REQUIRE(42 == l1.back());
}





//Aufgabe 4.4

TEST_CASE("should be empty after clearing", "[aufgabe4.4]") {
  List<int> list; 
  list.push_front(1); 
  list.push_front(2); 
  list.push_front(3); 
  list.push_front(4); 
  list.clear(); 
  REQUIRE(list.empty());
}






//Aufgabe 4.6
TEST_CASE("should be an empty range after default construction", "[aufgabe4.6]") {
  List<int> list;
  auto b = list.begin(); 
  auto e = list.end(); 
  REQUIRE(b == e);
}

TEST_CASE("provide acces to the first element with begin", "[aufgabe4.6]") {
  List<int> list; 
  list.push_front(42); 
  REQUIRE(42 == *list.begin());
}  


// Aufgabe 4.7
TEST_CASE("schaut ob gleich", "[aufgabe4.7]") {
  List<int> l1 {};
  l1.push_back(42); 
  l1.push_back(14);
  l1.push_back(39);
  List<int> l2 {};
  l2.push_back(42);
  l2.push_back(14);
  l2.push_back(39);
  REQUIRE(l1 == l2);
}

TEST_CASE("schaut ob ungleich", "[aufgabe4.7]") {
  List<int> l1 {};
  l1.push_back(42); 
  l1.push_back(14);
  l1.push_back(39);
  List<int> l2 {};
  l2.push_back(42);
  l2.push_back(14);
  l2.push_back(16);
  REQUIRE(l1 != l2);
}

//Aufgabe4.8
TEST_CASE("copy constructor", "[aufgabe4.8]") {
  List<int> list; 
  list.push_front(1); 
  list.push_front(2); 
  list.push_front(3); 
  list.push_front(4); 
  List<int> list2{list}; 
  REQUIRE(list == list2);;
}



//Aufgabe 4.9
TEST_CASE("inserts a value at certain position", "[aufgabe4.8]") {
  List<int> list;  // wenn am anfang
  list.push_front(14); 
  list.push_front(42); 
  list.push_front(13); 
  list.push_front(161);  
  list.insert(list.begin(), 25);
  REQUIRE(5 == list.size());
  REQUIRE(25 == list.front());
  REQUIRE(14 == list.back());


  List<int> list2; // wenn am ende
  list2.push_front(14); 
  list2.push_front(42); 
  list2.push_front(13); 
  list2.push_front(161);  
  list2.insert(list2.end(), 25);
  REQUIRE(5 == list2.size());
  REQUIRE(161 == list2.front());
  REQUIRE(25 == list2.back());


  List<int> list3; // sonst
  list3.push_front(14); 
  list3.push_front(42); 
  list3.push_front(13); 
  list3.push_front(32);
  list3.push_front(161); 
  ListIterator<int> pos = list3.begin();
  pos++; // operator test
  ++pos;
  ++pos; // pos zeigt jetzt auf position 3
  list3.insert(pos, 25);
  REQUIRE(6 == list3.size());
  REQUIRE(161 == list3.front());
  REQUIRE(14 == list3.back());
  ListIterator<int> it = list3.begin();
  REQUIRE(161 == *it); // pos = 0 / list.begin 
  ++it; 
  REQUIRE(32 == *it); // pos = 1 
  ++it;
  REQUIRE(13 == *it); // pos = 2 
  ++it;
  REQUIRE(25 == *it); // pos = 3
}

//Aufgabe 4.10

TEST_CASE("reverse", "[aufgabe4.10]") {
    //normal
  List<int> list; 
  list.push_back(4); 
  list.push_back(8); 
  list.push_back(3); 
  list.push_back(7); 
  list.push_back(12);
  list.reverse();
  ListIterator<int> it = list.begin();
  REQUIRE(12 == *it);
  ++it;
  REQUIRE(7 == *it);
  ++it; 
  REQUIRE(3 == *it);
  ++it;
  REQUIRE(8 == *it);
  ++it; 
  REQUIRE(4 == *it);

    // frei
  reverse(list);
  ListIterator<int> i = list.begin();
  REQUIRE(12 == *i);
  ++i;
  REQUIRE(7 == *i);
  ++i; 
  REQUIRE(3 == *i);
  ++i;
  REQUIRE(8 == *i);
  ++i; 
  REQUIRE(4 == *i);

}

//Aufgabe 4.13

TEST_CASE("move constructor", "[aufgabe4.13]") {
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);

  List<int> list2(std::move(list));
  REQUIRE(0 == list.size());
  REQUIRE(list.empty());
  REQUIRE(4 == list2.size());
}



int main(int argc, char * argv[]) {

  return Catch::Session().run(argc, argv);

}
