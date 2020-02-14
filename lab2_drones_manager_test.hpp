#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager1;

		ASSERT_TRUE(manager1.get_size() == 0)
		ASSERT_TRUE(manager1.empty() == true)
		ASSERT_FALSE(manager1.first != NULL)
		ASSERT_FALSE(manager1.last != NULL)
	    return true;
	}

	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;

		manager1.insert_front(DronesManager::DroneRecord(1));
		manager2.insert_back(DronesManager::DroneRecord(1));


		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)

		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)

		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)

		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(1))

		manager1.insert_back(DronesManager::DroneRecord(2));
		manager2.insert_front(DronesManager::DroneRecord(2));

		ASSERT_TRUE(*manager1.last == DronesManager::DroneRecord(2))
		ASSERT_TRUE(*manager2.first == DronesManager::DroneRecord(2))

	    return true;
	}

	// TODO: Implement all of the test cases below

	// PURPOSE: select() and search() work properly
	bool test3() {
	    DronesManager manager1, manager2;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);
	    DronesManager::DroneRecord d(3);
	    DronesManager::DroneRecord e(4);

	    manager2.insert_front(d);
	    manager2.insert_front(c);
	    manager2.insert_front(b);

	    ASSERT_TRUE(manager1.select(3) == a)
	    ASSERT_TRUE(manager1.select(-5) == a)
	    ASSERT_TRUE(manager1.select(0) == a)

	    ASSERT_TRUE(manager2.select(2) == d)
	    ASSERT_TRUE(manager2.select(0) == b)
	    ASSERT_TRUE(manager2.select(5) == d)

	    ASSERT_TRUE(manager1.search(a) == 0)
	    ASSERT_TRUE(manager1.search(b) == 0)
	    ASSERT_TRUE(manager1.search(c) == 0)

	    ASSERT_TRUE(manager2.search(b) == 0)
	    ASSERT_TRUE(manager2.search(e) == 3)

	    return true;
	}

	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {

        DronesManager manager1, manager2, manager3, manager4;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

	    manager1.insert_front(c);
	    manager1.insert_front(b);
	    manager1.insert_front(a);

	    manager2.insert_front(c);
	    manager2.insert_front(b);
	    manager2.insert_front(a);

	    manager1.remove_front();
	    manager2.remove_back();

	    manager3.insert_front(a);
	    manager4.insert_front(a);

	    manager3.remove_front();
	    manager4.remove_back();

	    ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 2)
		ASSERT_TRUE(manager1.select(0) == manager2.select(1) && manager1.select(manager1.size-2) == manager2.select(manager2.size-1))
		ASSERT_TRUE(manager3.get_size() == 0 && manager4.get_size() == 0)
		ASSERT_TRUE(manager3.first == NULL && manager3.last == NULL)
		ASSERT_TRUE(manager4.first == NULL && manager4.last == NULL)

	    return true;
	}

	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
	    DronesManager manager1, manager2, manager3;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

	    manager1.insert_front(c);
	    manager1.insert_front(b);
	    manager1.insert_front(a);

	    manager2.insert_front(c);
	    manager2.insert_front(b);
	    manager2.insert_front(a);

	    manager3.insert_front(a);

	    // first and last elements of manager1 should equal first and last elements of reversed manager2
	    manager1.replace(0,c);
	    manager1.replace(1,c);
	    manager1.replace(2,a);

	    manager2.reverse_list();

	    manager3.replace(0,b);

	    // check to make sure that using replace() with an invalid index will return false
        ASSERT_FALSE(manager1.replace(5,a))
        // check to make sure corresponding values that should be equal are equal
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(2) == manager2.select(2))
        // check to make sure replace() with a single element list works
        ASSERT_TRUE(manager3.first == manager3.last && manager3.select(0) == manager2.select(1))

	    return true;
	}

	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
	    DronesManager manager1;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

	    manager1.insert_front(c);
	    manager1.insert_front(b);
	    manager1.insert_front(a);

	    // if elements are moved forward, order should be a,b,c (from first to last)
	    ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(0))
	    ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(2))

	    return true;
	}

	// PURPOSE: inserting at different positions in the list
	bool test7() {
        DronesManager manager1;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

	    manager1.insert_front(a);
	    manager1.insert(c,1);
	    manager1.insert(b,1);

	    // if elements are moved forward, order should be a,b,c (from first to last)
	    ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(0))
	    ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(2))
	    // show that insert() function does not work when index is larger than size
	    ASSERT_FALSE(manager1.insert(b,4))
	    return true;
	}

	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
        DronesManager manager1;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

	    // SHOULD BE USING insert_front
	    manager1.insert_front(b);
	    manager1.insert_front(a);

	    manager1.remove_front();
	    manager1.remove_front();

	    // manager1 should now be empty
	    ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL)
	    // trying to remove more elements from an empty manager1 returns false
	    ASSERT_FALSE(manager1.remove_front())

	    // add a couple other elements
	    manager1.insert_front(b);
	    manager1.insert(a,1);
	    manager1.insert(c,2);

	    ASSERT_TRUE(*manager1.first == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(*manager1.last == DronesManager::DroneRecord(2))

	    return true;
	}

	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
	    DronesManager manager1;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

	    manager1.insert_front(a);
	    manager1.insert(b,2); // invalid
	    manager1.remove(2); // invalid
	    manager1.insert(b,1);
	    manager1.remove_front(); // manager1 should be just b now
	    manager1.insert(c,1);
	    manager1.insert(a,2); //b,c,a
	    manager1.remove(3); // invalid, since size is 3, elements go up to index 2

	    // final order of manager1 should be b,c,a (from first to last)
	    ASSERT_TRUE(*manager1.first == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(*manager1.last == DronesManager::DroneRecord(0))
	    ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(2))

		return true;
	}

	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
        DronesManager manager1;
	    DronesManager::DroneRecord a(0);
	    DronesManager::DroneRecord b(1);
	    DronesManager::DroneRecord c(2);

        // insert 8 elements
	    manager1.insert_front(a);
	    manager1.insert_front(b);
	    manager1.insert_front(c);
	    manager1.insert_front(c);
	    manager1.insert_front(b);
	    manager1.insert_front(c);
	    manager1.insert_front(a);
	    manager1.insert_front(b);

	    // order of the list should be b,a,c,b,c,c,b,a
	    ASSERT_TRUE(*manager1.first == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(*manager1.last == DronesManager::DroneRecord(0))
	    ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(manager1.select(4) == DronesManager::DroneRecord(2))
	    ASSERT_TRUE(manager1.select(6) == DronesManager::DroneRecord(1))

	    manager1.reverse_list();

	    // order of the list after reversing should be a,b,c,c,b,c,a,b

	    ASSERT_TRUE(*manager1.first == DronesManager::DroneRecord(0))
	    ASSERT_TRUE(*manager1.last == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(manager1.select(3) == DronesManager::DroneRecord(2))
	    ASSERT_TRUE(manager1.select(4) == DronesManager::DroneRecord(1))
	    ASSERT_TRUE(manager1.select(6) == DronesManager::DroneRecord(0))

	    // keep removing elements until elements can no longer be removed
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_TRUE(manager1.remove_front())
	    ASSERT_FALSE(manager1.remove_front())

        return true;
	}
};

#endif
