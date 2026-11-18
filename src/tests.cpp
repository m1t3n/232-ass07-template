#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <cmath>
#include <iostream>
#include <numbers>

// ============================================================
// PART 1 Tests: Shapes
// ============================================================

/// Create Circle(1), Square(2), Rectangle(2, 3).
/// Verify area() is pi, 4 and 6 (compare doubles with std::fabs(a - b) < 1e-9).
void test_shape_areas(void)
{
    Circle x(1);
    Square y(2);
    Rectangle z(2,3);
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(x.area() - std::numbers::pi) < 1e-9, "circle is wrong");
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(y.area() - 4) < 1e-9, "square is wrong");
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(z.area() - 6) < 1e-9, "rectangle is wrong");
}

/// Create an array of three Shape* (a Circle, a Square, a Rectangle) with new.
/// Verify name() through the BASE pointer gives "Circle", "Square", "Rectangle".
/// Delete the shapes through the base pointers.
void test_shape_names_through_base_pointer(void)
{
    Shape* arr[] = {new Circle(3), new Square(4), new Rectangle(2,5)};
    
    TEST_ASSERT_TRUE_MESSAGE(arr[0]->name()=="Circle", "it's not circle");
    TEST_ASSERT_TRUE_MESSAGE(arr[1]->name()=="Square", "it's not square");
    TEST_ASSERT_TRUE_MESSAGE(arr[2]->name()=="Rectangle", "it's not rectangle");
}

/// Create Square(1) and Square(2). Take two const Shape& to them.
/// Verify small < big is true, big < small is false, small < small is false.
void test_shape_operator_less(void)
{
    Square x = Square(1);
    Square y = Square(2);
    const Shape& small = x;
    const Shape& big = y;

    TEST_ASSERT_TRUE_MESSAGE(small<big, "small not less than big");
    TEST_ASSERT_TRUE_MESSAGE((big<small)==false, "big less than small");
    TEST_ASSERT_TRUE_MESSAGE((small<small)==false, "small less than itself");
}

/// Create Square(2) and Rectangle(1, 4): both have area 4.
/// Verify that NEITHER a < b NOR b < a is true.
void test_shape_equal_area_not_less(void)
{
    Square x = Square(2);
    Rectangle y = Rectangle(1,4);

    TEST_ASSERT_TRUE_MESSAGE((x<y)==false, "x<y");
    TEST_ASSERT_TRUE_MESSAGE((y<x)==false, "y<x");
}

// ============================================================
// PART 2 Tests: ShapeList
// ============================================================

/// Create a ShapeList. Add new Circle(1) and new Square(2) with addShape.
/// Verify both calls return 0 and length() is 2.
/// (Do NOT delete the shapes yourself: the list owns them.)
void test_list_add_and_length(void)
{
    ShapeList list;

    TEST_ASSERT_TRUE_MESSAGE(list.addShape(new Circle(1))==0, "circle does not equal 0");
    TEST_ASSERT_TRUE_MESSAGE(list.addShape(new Square(2))==0, "square does not equal 0");
    TEST_ASSERT_TRUE_MESSAGE(list.length()==2, "length does not equal 2");
}

/// Create a ShapeList. Call addShape(nullptr).
/// Verify it returns -1 and length() stays 0.
void test_list_add_null_guard(void)
{
    ShapeList list;
    TEST_ASSERT_TRUE_MESSAGE(list.addShape(nullptr)==-1, "doesn't return -1");
    TEST_ASSERT_TRUE_MESSAGE(list.length()==0, "length isn't 0");
}

/// Add Rectangle(2, 5) (area 10), Circle(1) (area 3.14), Square(2) (area 4).
/// Call insertionSort(). Verify nameAt(0), nameAt(1), nameAt(2) are
/// "Circle", "Square", "Rectangle" and isSorted() is true.
void test_insertionSort_orders_by_area(void)
{
    ShapeList list;
    list.addShape(new Rectangle(2,5));
    list.addShape(new Circle(1));
    list.addShape(new Square(2));
    list.insertionSort();
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(0)=="Circle", "not circle");
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(1)=="Square", "not square");
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(2)=="Rectangle", "not rectangle");
    TEST_ASSERT_TRUE_MESSAGE(list.isSorted()==true, "not sorted");
}

/// Call insertionSort() on an EMPTY list: no crash, length() is 0.
/// Then add ONE shape and sort again: length() is 1 and nameAt(0) is unchanged.
void test_insertionSort_empty_and_single(void)
{
    ShapeList list;
    list.insertionSort();
    TEST_ASSERT_TRUE_MESSAGE(list.length()==0, "length is not 0");

    list.addShape(new Circle(1));
    list.insertionSort();
    TEST_ASSERT_TRUE_MESSAGE(list.length()==1, "length is not 0");
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(0)=="Circle", "nameAt is not circle");
}
