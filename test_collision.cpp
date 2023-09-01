//-----------------------------------------------------------------------------
// Copyright (c) 2005-2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "test_main.h"

void TestMathCollision();
void DoPlaneTest();
void DoRayTest();

//-----------------------------------------------------------------------------
// Tests all of the collision related math classes.
//-----------------------------------------------------------------------------

void TestMathCollision()
{
    DoPlaneTest();
    DoRayTest();
}

//-----------------------------------------------------------------------------
// Unit test the Plane class. This is not an exhaustive test of the
// Plane class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoPlaneTest()
{
    // Test 1: Plane equality.
    {
        Plane p(0.0f, 1.0f, 0.0f, 0.0f);

        if (p != p)
            throw std::runtime_error("DoPlaneTest() : Plane equality failed");
    }

    // Test 2: Plane from point normal.
    {
        Plane p;

        p.fromPointNormal(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

        if (p != Plane(0.0f, 0.0f, 1.0f, 0.0f))
            throw std::runtime_error("DoPlaneTest() : Plane from point normal failed");
    }

    // Test 3: Plane from points.
    {
        Plane p;
        Vector3 pts[3] =
        {
            Vector3( 0.0f,  1.0f, 0.0f),
            Vector3(-1.0f, -1.0f, 0.0f),
            Vector3( 1.0f, -1.0f, 0.0f)
        };

        p.fromPoints(pts[0], pts[1], pts[2]);

        if (p != Plane(0.0f, 0.0f, 1.0f, 0.0f))
            throw std::runtime_error("DoPlaneTest() : Plane from points failed");
    }

    // Test 4: Plane normal.
    {
        Plane p(0.0f, 0.0f, 1.0f, 0.0f);

        if (p.normal() != Vector3(0.0f, 0.0f, 1.0f))
            throw std::runtime_error("DoPlaneTest() : Plane normal failed");
    }

    // Test 5: Plane normalize.
    {
        Plane p(0.0f, 0.0f, 2.0f, 0.0f);

        p.normalize();

        if (p != Plane(0.0f, 0.0f, 1.0f, 0.0f))
            throw std::runtime_error("DoPlaneTest() : Plane normalize failed");
    }

    // Test 6: Plane dot product.
    {
        Plane p(0.0f, 0.0f, 1.0, 0.0f);

        // Case 1: Point on plane.
        if (!Math::closeEnough(Plane::dot(p, Vector3(0.0f, 0.0f, 0.0f)), 0.0f))
            throw std::runtime_error("DoPlaneTest() : Plane dot product case 1 failed");

        // Case 2: Point in front of plane.
        if (Plane::dot(p, Vector3(0.0f, 0.0f, 1.0f)) <= 0.0f)
            throw std::runtime_error("DoPlaneTest() : Plane dot product case 2 failed");

        // Case 3: Point behind plane.
        if (Plane::dot(p, Vector3(0.0f, 0.0f, -1.0f)) >= 0.0f)
            throw std::runtime_error("DoPlaneTest() : Plane dot product case 3 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Ray class. This is not an exhaustive test of the
// Ray class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoRayTest()
{
    Vector3 origin(0.0f, 0.0f, 0.0f);
    BoundingSphere sphere(origin, 10.0f);

    // Test 1: Ray hits a bounding sphere that the ray is inside of.
    {
        Ray ray(origin, Vector3(0.0f, 0.0f, 1.0f));

        if (!ray.hasIntersected(sphere))
            throw std::runtime_error("DoRayTest() : Test 1 failed");
    }

    // Test 2: Ray hits a bounding sphere.
    {
        Ray ray(Vector3(0.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, -1.0f));

        if (!ray.hasIntersected(sphere))
            throw std::runtime_error("DoRayTest() : Test 2 failed");
    }

    // Test 3: Ray misses a bounding sphere.
    {
        Ray ray(Vector3(0.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, 1.0f));

        if (ray.hasIntersected(sphere))
            throw std::runtime_error("DoRayTest() : Test 3 failed");
    }

    BoundingBox box(Vector3(-10.0f, -10.0f, -10.0f), Vector3(10.0f, 10.0f, 10.0f));

    // Test 4: Ray hits a bounding box that the ray is inside of.
    {
        Ray ray(origin, Vector3(0.0f, 0.0f, 1.0f));

        if (!ray.hasIntersected(box))
            throw std::runtime_error("DoRayTest() : Test 4 failed");
    }

    // Test 5: Ray hits a bounding box.
    {
        Ray ray(Vector3(0.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, -1.0f));

        if (!ray.hasIntersected(box))
            throw std::runtime_error("DoRayTest() : Test 5 failed");
    }

    // Test 6: Ray misses a bounding box.
    {
        Ray ray(Vector3(0.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, 1.0f));

        if (ray.hasIntersected(box))
            throw std::runtime_error("DoRayTest() : Test 6 failed");
    }

    Plane xzPlane(origin, Vector3(0.0f, 1.0f, 0.0f));

    // Test 7: Ray intersects a plane.
    {
        Ray ray(Vector3(0.0f, 10.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));

        if (!ray.hasIntersected(xzPlane))
            throw std::runtime_error("DoRayTest() : Test 7 failed");
    }

    // Test 8: Ray misses a plane.
    {
        Ray ray(Vector3(0.0f, 10.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

        if (ray.hasIntersected(xzPlane))
            throw std::runtime_error("DoRayTest() : Test 8 failed");
    }

    // Test 9: Line segment intersects a plane.
    {
        Vector3 pt1(0.0f, -10.0f, 0.0f);
        Vector3 pt2(0.0f, 10.0f, 0.0f);
        Ray ray(pt1, pt2 - pt1);

        if (!ray.hasIntersected(xzPlane))
            throw std::runtime_error("DoRayTest() : Test 9 failed");
    }

    // Test 10: Line segment misses a plane.
    {
        Vector3 pt1(0.0f, 10.0f, 0.0f);
        Vector3 pt2(0.0f, 20.0f, 0.0f);
        Ray ray(pt1, pt2 - pt1);

        if (ray.hasIntersected(xzPlane))
            throw std::runtime_error("DoRayTest() : Test 10 failed");
    }
}