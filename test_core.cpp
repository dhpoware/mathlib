//-----------------------------------------------------------------------------
// Copyright (c) 2005-2008 dhpoware. All Rights Reserved.
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

void TestMathCore();
void DoCommonTest();
void DoVector2Test();
void DoVector3Test();
void DoVector4Test();
void DoMatrix3Test();
void DoMatrix4Test();
void DoQuaternionTest();
void DoMatrixStackTest();

//-----------------------------------------------------------------------------
// Tests all of the core math classes.
//-----------------------------------------------------------------------------

void TestMathCore()
{
    DoCommonTest();
    DoVector2Test();
    DoVector3Test();
    DoVector4Test();
    DoMatrix3Test();
    DoMatrix4Test();
    DoQuaternionTest();
	DoMatrixStackTest();
}

//-----------------------------------------------------------------------------
// Test functions common to all of the math classes.
//-----------------------------------------------------------------------------

void DoCommonTest()
{
    float result = (1.0f / 10.0f) * 10.0f;

    if (!Math::closeEnough(result, 1.0f))
        throw std::runtime_error("DoCommonTest() : closeEnough() failed");

    if (!Math::closeEnough(Math::radiansToDegrees(Math::PI), 180.0f))
        throw std::runtime_error("DoCommonTest() : radiansToDegrees() failed");

    if (!Math::closeEnough(Math::degreesToRadians(180.0f), Math::PI))
        throw std::runtime_error("DoCommonTest() : degreesToRadians() failed");

    if (Math::floatToLong(1.8f) != 1)
        throw std::runtime_error("DoCommonTest() : floatToLong() failed");

    if (Math::nextMultipleOf(2, 3) != 4)
        throw std::runtime_error("DoCommonTest() : nextMultipleOf() failed");

    // LERP tests.
    {
        // Case 1: When t == 0, result is -90.
        if (!Math::closeEnough(-90.0f, Math::lerp(-90.0f, 90.0f, 0.0f)))
            throw std::runtime_error("DoCommonTest() : lerp() Case 1 failed");

        // Case 2: When t == 1, result is 90.
        if (!Math::closeEnough(90.0f, Math::lerp(-90.0f, 90.0f, 1.0f)))
            throw std::runtime_error("DoCommonTest() : lerp() Case 2 failed");

        // Case 3: When t == 0.5, result is 0.
        if (!Math::closeEnough(0.0f, Math::lerp(-90.0f, 90.0f, 0.5f)))
            throw std::runtime_error("DoCommonTest() : lerp() Case 3 failed");
    }
    
    // Spherical Coordinates tests.
    {
        Vector3 origPt(10.0f, 20.0f, 30.0f), result(0.0f, 0.0f, 0.0f);
        float rho = 0.0f, phi = 0.0f, theta = 0.0f;

        Math::cartesianToSpherical(origPt.x, origPt.y, origPt.z, rho, phi, theta);
        Math::sphericalToCartesian(rho, phi, theta, result.x, result.y, result.z);

        if (origPt != result)
            throw std::runtime_error("DoCommonTest() : Spherical Coordinates failed");
    }

    // Power of 2 tests.
    {
        // Case 1.
        if (!Math::isPower2(2))
            throw std::runtime_error("DoCommonTest() : isPower2() Case 1 failed");

        // Case 2.
        if (Math::isPower2(0))
            throw std::runtime_error("DoCommonTest() : isPower2() Case 2 failed");

        // Case 3.
        if (Math::isPower2(-2))
            throw std::runtime_error("DoCommonTest() : isPower2() Case 3 failed");

        if (Math::nextPower2(3) != 4)
            throw std::runtime_error("DoCommonTest() : nextPower2() failed");
    }

    // Smoothstep tests.
    {
        // Case 1.
        if (Math::smoothstep(1.0f, 2.0f, 0.0f) != 0.0f)
            throw std::runtime_error("DoCommonTest() : smoothstep() case 1 failed");

        // Case 2.
        if (Math::smoothstep(1.0f, 2.0f, 3.0f) != 1.0f)
            throw std::runtime_error("DoCommonTest() : smoothstep() case 2 failed");

        float result = Math::smoothstep(1.0f, 2.0f, 1.5f);

        // Case 3.
        if (result < 0.0f || result > 1.0f)
            throw std::runtime_error("DoCommonTest() : smoothstep() case 3 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Vector2 class. This is not an exhaustive test of the
// Vector2 class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoVector2Test()
{
    // Test 1. Multiply by a scalar.
    {
        Vector2 v(1.0f, 1.0f);

        if (v * 7.0f != Vector2(7.0f, 7.0f))
            throw std::runtime_error("DoVector2Test() : Test 1 failed");
    }

    // Test 2. Divide by a scalar.
    {
        Vector2 v(2.0f, 2.0f);

        if (v / 2.0f != Vector2(1.0f, 1.0f))
            throw std::runtime_error("DoVector2Test() : Test 2 failed");
    }

    // Test 3. Add 2 vectors.
    {
        Vector2 v = Vector2(1.0f, 1.0f) + Vector2(1.0f, 1.0f);

        if (v != Vector2(2.0f, 2.0f))
            throw std::runtime_error("DoVector2Test() : Test 3 failed");
    }

    // Test 4. Subtract 2 vectors.
    {
        Vector2 v = Vector2(2.0f, 2.0f) - Vector2(2.0f, 2.0f);

        if (v != Vector2(0.0f, 0.0f))
            throw std::runtime_error("DoVector2Test() : Test 4 failed");
    }

    // Test 5: Vector equality.
    {
        Vector2 v(1.0f, 1.0f);

        if (v != v)
            throw std::runtime_error("DoVector2Test() : Test 5 failed");
    }

    // Test 6: Vector magnitude.
    {
        Vector2 v(1.0f, 0.0f);

        if (!Math::closeEnough(v.magnitude(), 1.0f))
            throw std::runtime_error("DoVector2Test() : Test 6 failed");
    }

    // Test 7: Vector normalize.
    {
        Vector2 v(2.0f, 0.0f);

        v.normalize();

        if (v != Vector2(1.0f, 0.0f))
            throw std::runtime_error("DoVector2Test() : Test 7 failed");
    }

    // Test 8: Vector dot product.
    {
        // Case 1: Angular displacement is 90 degrees (perpendicular).
        float f = Vector2::dot(Vector2(1.0f, 0.0f), Vector2(0.0f, 1.0f));
        
        if (!Math::closeEnough(f, 0.0f))
            throw std::runtime_error("DoVector2Test() : Test 8 Case 1 failed");

        // Case 2: Angular displacement less than 90 degrees (acute).
        f = Vector2::dot(Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f));

        if (f <= 0.0f)
            throw std::runtime_error("DoVector2Test() : Test 8 Case 2 failed");

        // Case 3: Angular displacement greater than 90 degrees (obtuse).
        f = Vector2::dot(Vector2(-1.0f, 0.0f), Vector2(1.0f, 0.0f));

        if (f >= 0)
            throw std::runtime_error("DoVector2Test() : Test 8 Case 3 failed");
    }

    // Test 9: Vector projection.
    {
        Vector2 v = Vector2::proj(Vector2(2.0f, 3.0f), Vector2(1.0f, 1.0f));

        if (v != Vector2(5.0f / 2.0f, 5.0f / 2.0f))
            throw std::runtime_error("DoVector2Test() : Test 9 failed");
    }

    // TODO - Test 10: Vector perpendicular projection.
    {
    }

    // Test 11: Vector inverse.
    {
        if (-Vector2(1.0f, 1.0f) != Vector2(-1.0f, -1.0f))
            throw std::runtime_error("DoVector2Test() : Test 11 failed");
    }

    // Test 12: Vector reflection.
    {
        Vector2 i = Vector2(0.0f, 0.0f) - Vector2(-1.0f, 1.0f);
        Vector2 result = Vector2::reflect(i, Vector2(0.0f, 1.0f));
        Vector2 expected = Vector2(1.0f, 1.0f) - Vector2(0.0f, 0.0f);

        if (result != expected)
            throw std::runtime_error("DoVector2Test() : Test 12 failed");
    }

    // Test 13: Vector linear interpolation.
    {
        Vector2 a(0.0f, 0.0f);
        Vector2 b(0.5f, 0.0f);
        Vector2 c(1.0f, 0.0f);

        // Case 1.
        if (Vector2::lerp(a, c, 0.0f) != a)
            throw std::runtime_error("DoVector2Test() : Test 13 Case 1 failed");

        // Case 2.
        if (Vector2::lerp(a, c, 0.5f) != b)
            throw std::runtime_error("DoVector2Test() : Test 13 Case 2 failed");

        // Case 3.
        if (Vector2::lerp(a, c, 1.0f) != c)
            throw std::runtime_error("DoVector2Test() : Test 13 Case 3 failed");
    }

    // Test 14: Distance between 2 points.
    {
        Vector2 pt1(0.0f, 0.0f);
        Vector2 pt2(1.0f, 0.0f);

        if (!Math::closeEnough(Vector2::distance(pt1, pt2), 1.0f))
            throw std::runtime_error("DoVector2Test() : Test 14 failed");
    }

    // Test 15: Orthogonalize 2 basis vectors.
    {
        const Vector2 xAxis(1.0f, 0.0f);
        const Vector2 yAxis(0.0f, 1.0f);

        float theta = Math::degreesToRadians(45.0f);

        Vector2 axis1 = xAxis;
        Vector2 axis2(cosf(theta), sinf(theta));

        Vector2::orthogonalize(axis1, axis2);

        if (!(axis1 == xAxis && axis2 == yAxis))
            throw std::runtime_error("DoVector2Test() : Test 15 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Vector3 class. This is not an exhaustive test of the
// Vector3 class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoVector3Test()
{
    // Test 1. Multiply by a scalar.
    {
        Vector3 v(1.0f, 0.0f, 0.0f);

        if ((v * 7.0f) != Vector3(7.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoVector3Test() : Test 1 failed");
    }

    // Test 2. Divide by a scalar.
    {
        Vector3 v(2.0f, 0.0f, 0.0f);

        if ((v / 2.0f) != Vector3(1.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoVector3Test() : Test 2 failed");
    }

    // Test 3. Add 2 vectors.
    {
        Vector3 v = Vector3(1.0f, 1.0f, 1.0f) + Vector3(1.0f, 1.0f, 1.0f);

        if (v != Vector3(2.0f, 2.0f, 2.0f))
            throw std::runtime_error("DoVector3Test() : Test 3 failed");
    }

    // Test 4. Subtract 2 vectors.
    {
        Vector3 v = Vector3(2.0f, 2.0f, 2.0f) - Vector3(2.0f, 2.0f, 2.0f);

        if (v != Vector3(0.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoVector3Test() : Test 4 failed");
    }

    // Test 5: Vector equality.
    {
        Vector3 v(1.0f, 0.0f, 0.0f);

        if (v != v)
            throw std::runtime_error("DoVector3Test() : Test 5 failed");
    }

    // Test 6: Vector magnitude.
    {
        Vector3 v(1.0f, 0.0f, 0.0f);

        if (!Math::closeEnough(v.magnitude(), 1.0f))
            throw std::runtime_error("DoVector3Test() : Test 6 failed");
    }

    // Test 7: Vector normalize.
    {
        Vector3 v(2.0f, 0.0f, 0.0f);

        v.normalize();

        if (v != Vector3(1.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoVector3Test() : Test 7 failed");
    }

    // Test 8: Vector cross product.
    {
        Vector3 zAxis = Vector3::cross(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

        if (zAxis != Vector3(0.0f, 0.0f, 1.0f))
            throw std::runtime_error("DoVector3Test() : Test 8 failed");
    }

    // Test 9: Vector dot product.
    {
        float f = Vector3::dot(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

        // Case 1: Angular displacement is 90 degrees (perpendicular).
        if (!Math::closeEnough(f, 0.0f))
            throw std::runtime_error("DoVector3Test() : Test 9 Case 1 failed");

        // Case 2: Angular displacement less than 90 degrees (acute).
        f = Vector3::dot(Vector3(1.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

        if (f <= 0.0f)
            throw std::runtime_error("DoVector3Test() : Test 9 Case 2 failed");

        // Case 3: Angular displacement greater than 90 degrees (obtuse).
        f = Vector3::dot(Vector3(-1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

        if (f >= 0.0f)
            throw std::runtime_error("DoVector3Test() : Test 9 Case 3 failed");
    }

    // Test 10: Vector projection.
    {
        Vector3 v = Vector3::proj(Vector3(1.0f, -2.0f, 0.0f), Vector3(2.0f, 2.0f, 1.0f));

        if (v != Vector3(-4.0f/9.0f, -4.0f/9.0f, -2.0f/9.0f))
            throw std::runtime_error("DoVector3Test() : Test 10 failed");
    }

    // TODO - Test 11: Vector perpendicular projection.
    {
    }

    // Test 12: Vector inverse.
    {
        if (-Vector3(1.0f, 1.0f, 1.0f) != Vector3(-1.0f, -1.0f, -1.0f))
            throw std::runtime_error("DoVector3Test() : Test 12 failed");
    }

    // Test 13: Vector reflection.
    {
        Vector3 i = Vector3(0.0f, 0.0f, 0.0f) - Vector3(-1.0f, 1.0f, 0.0f);
        Vector3 result = Vector3::reflect(i, Vector3(0.0f, 1.0f, 0.0f));
        Vector3 expected = Vector3(1.0f, 1.0f, 0.0f) - Vector3(0.0f, 0.0f, 0.0f);
        
        if (result != expected)
            throw std::runtime_error("DoVector3Test() : Test 13 failed");
    }

    // Test 14: Vector linear interpolation.
    {
        Vector3 a(0.0f, 0.0f, 0.0f);
        Vector3 b(0.0f, 0.0f, 0.5f);
        Vector3 c(0.0f, 0.0f, 1.0f);

        // Case 1.
        if (Vector3::lerp(a, c, 0.0f) != a)
            throw std::runtime_error("DoVector3Test() : Test 14 Case 1 failed");

        // Case 2.
        if (Vector3::lerp(a, c, 0.5f) != b)
            throw std::runtime_error("DoVector3Test() : Test 14 Case 2 failed");

        // Case 3.
        if (Vector3::lerp(a, c, 1.0f) != c)
            throw std::runtime_error("DoVector3Test() : Test 14 Case 3 failed");
    }

    // Test 15: Distance between 2 points.
    {
        Vector3 pt1(0.0f, 0.0f, 0.0f);
        Vector3 pt2(1.0f, 0.0f, 0.0f);
        
        if (!Math::closeEnough(Vector3::distance(pt1, pt2), 1.0f))
            throw std::runtime_error("DoVector3Test() : Test 15 failed");
    }

    // Test 16: Orthogonalize 2 basis vectors.
    {
        const Vector3 xAxis(1.0f, 0.0f, 0.0f);
        const Vector3 yAxis(0.0f, 1.0f, 0.0f);

        float theta = Math::degreesToRadians(45.0f);

        Vector3 axis1 = xAxis;
        Vector3 axis2(cosf(theta), sinf(theta), 0.0f);

        Vector3::orthogonalize(axis1, axis2);

        if (!(axis1 == xAxis && axis2 == yAxis))
            throw std::runtime_error("DoVector3Test() : Test 16 failed");
    }

    // Test 17: Orthogonalize 3 basis vectors.
    {
        const Vector3 xAxis(1.0f, 0.0f, 0.0f);
        const Vector3 yAxis(0.0f, 1.0f, 0.0f);
        const Vector3 zAxis(0.0f, 0.0f, 1.0f);

        float theta = Math::degreesToRadians(45.0f);

        Vector3 axis1 = xAxis;
        Vector3 axis2(cosf(theta), sinf(theta), 0.0f);
        Vector3 axis3(cosf(theta), 0.0f, sinf(theta));

        Vector3::orthogonalize(axis1, axis2, axis3);

        if (!(axis1 == xAxis && axis2 == yAxis && axis3 == zAxis))
            throw std::runtime_error("DoVector3Test() : Test 17 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Vector4 class. This is not an exhaustive test of the
// Vector4 class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoVector4Test()
{
    // Test 1. Multiply by a scalar.
    {
        Vector4 v(1.0f, 0.0f, 0.0f, 1.0f);

        if ((v * 7.0f) != Vector4(7.0f, 0.0f, 0.0f, 7.0f))
            throw std::runtime_error("DoVector4Test() : Test 1 failed");
    }

    // Test 2. Divide by a scalar.
    {
        Vector4 v(7.0f, 0.0f, 0.0f, 7.0f);

        if ((v / 7.0f) != Vector4(1.0f, 0.0f, 0.0f, 1.0f))
            throw std::runtime_error("DoVector4Test() : Test 2 failed");
    }

    // Test 3. Add 2 vectors.
    {
        Vector4 v = Vector4(1.0f, 1.0f, 1.0f, 1.0f) + Vector4(1.0f, 1.0f, 1.0f, 1.0f);

        if (v != Vector4(2.0f, 2.0f, 2.0f, 2.0f))
            throw std::runtime_error("DoVector4Test() : Test 3 failed");
    }

    // Test 4. Subtract 2 vectors.
    {
        Vector4 v = Vector4(2.0f, 2.0f, 2.0f, 1.0f) - Vector4(2.0f, 2.0f, 2.0f, 1.0f);

        if (v != Vector4(0.0f, 0.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoVector4Test() : Test 4 failed");
    }

    // Test 5: Vector equality.
    {
        Vector4 v(1.0f, 0.0f, 0.0f, 1.0f);

        if (v != v)
            throw std::runtime_error("DoVector4Test() : Test 5 failed");
    }

    // Test 6: Vector magnitude.
    {
        Vector4 v(1.0f, 0.0f, 0.0f, 0.0f);

        if (!Math::closeEnough(v.magnitude(), 1.0f))
            throw std::runtime_error("DoVector4Test() : Test 6 failed");
    }

    // Test 7: Vector normalize.
    {
        Vector4 v(2.0f, 0.0f, 0.0f, 0.0f);

        v.normalize();

        if (v != Vector4(1.0f, 0.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoVector4Test() : Test 7 failed");
    }

    // Test 8: Vector inverse.
    {
        Vector4 v(1.0f, 1.0f, 1.0f, 0.0f);

        if (v.inverse() != Vector4(-1.0f, -1.0f, -1.0f, 0.0f))
            throw std::runtime_error("DoVector4Test() : Test 8 failed");
    }

    // Test 9: Vector linear interpolation.
    {
        Vector4 a(0.0f, 0.0f, 0.0f, 1.0f);
        Vector4 b(0.0f, 0.0f, 0.5f, 1.0f);
        Vector4 c(0.0f, 0.0f, 1.0f, 1.0f);

        // Case 1.
        if (Vector4::lerp(a, c, 0.0f) != a)
            throw std::runtime_error("DoVector4Test() : Test 9 Case 1 failed");

        // Case 2.
        if (Vector4::lerp(a, c, 0.5f) != b)
            throw std::runtime_error("DoVector4Test() : Test 9 Case 2 failed");

        // Case 3.
        if (Vector4::lerp(a, c, 1.0f) != c)
            throw std::runtime_error("DoVector4Test() : Test 9 Case 3 failed");
    }

    // Test 10: Distance between 2 points.
    {
        Vector4 pt1(0.0f, 0.0f, 0.0f, 1.0f);
        Vector4 pt2(1.0f, 0.0f, 0.0f, 1.0f);

        if (!Math::closeEnough(Vector4::distance(pt1, pt2), 1.0f))
            throw std::runtime_error("DoVector4Test() : Test 10 failed");
    }

    // Test 11: Transform a point.
    {      
        Matrix4 mtx;
        mtx.rotate(Vector3(0.0f, 0.0f, 1.0f), 90.0f);

        Vector4 pt(1.0f, 0.0f, 0.0f, 1.0f);
        Vector4 ptExpected(0.0f, 1.0f, 0.0f, 1.0f);
        Vector4 ptResult = pt * mtx;

        if (ptResult != ptExpected)
            throw std::runtime_error("DoVector4Test() : Test 11 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Matrix3 class. This is not an exhaustive test of the
// Matrix3 class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoMatrix3Test()
{
    // Test 1: Matrix equality.
    {
        Matrix3 m = Matrix3::IDENTITY;

        if (m != Matrix3::IDENTITY)
            throw std::runtime_error("DoMatrix3Test() : Test 1 failed");
    }

    // Test 2: Matrix orientation.
    {
        Matrix3 m;
        Vector3 from, to, result;

        // Case 1: Rotate the x-axis into the x-axis.
        from.set(1.0f, 0.0f, 0.0f);
        to.set(1.0f, 0.0f, 0.0f);
        m.orient(from, to);
        result = from * m;

        if (result != to)
            throw std::runtime_error("DoMatrix3Test() : Test 2 Case 1 failed");

        // Case 2: Rotate the x-axis into the negative x-axis.
        from.set(1.0f, 0.0f, 0.0f);
        to.set(-1.0f, 0.0f, 0.0f);
        m.orient(from, to);
        result = from * m;

        if (result != to)
            throw std::runtime_error("DoMatrix3Test() : Test 2 Case 2 failed");

        // Case 3: Rotate the x-axis into the y-axis.
        from.set(1.0f, 0.0f, 0.0f);
        to.set(0.0f, 1.0f, 0.0f);
        m.orient(from, to);
        result = from * m;

        if (result != to)
            throw std::runtime_error("DoMatrix3Test() : Test 2 Case 3 failed");
    }

    // Test 3: Matrix construction.
    {
        Matrix3 m(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f);

        if (m != Matrix3::IDENTITY)
            throw std::runtime_error("DoMatrix3Test() : Test 3 failed");
    }

    // Test 4: Matrix addition.
    {
        Matrix3 m(
            1.0f, 1.0f, 1.0f,
            2.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 3.0f);

        Matrix3 expected(
            2.0f, 1.0f, 1.0f,
            2.0f, 3.0f, 2.0f,
            3.0f, 3.0f, 4.0f);

        if (m + Matrix3::IDENTITY != expected)
            throw std::runtime_error("DoMatrix3Test() : Test 4 failed");
    }

    // Test 5: Matrix subtraction.
    {
        Matrix3 m(
            1.0f, 1.0f, 1.0f,
            2.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 3.0f);

        Matrix3 expected(
            0.0f, 1.0f, 1.0f,
            2.0f, 1.0f, 2.0f,
            3.0f, 3.0f, 2.0f);

        if (m - Matrix3::IDENTITY != expected)
            throw std::runtime_error("DoMatrix3Test() : Test 5 failed");
    }

    // Test 6: Matrix transpose.
    {
        Matrix3 m(
            1.0f, 1.0f, 1.0f,
            2.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 3.0f);

        Matrix3 expected(
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f,
            1.0f, 2.0f, 3.0f);

        if (m.transpose() != expected)
            throw std::runtime_error("DoMatrix3Test() : Test 6 failed");
    }

    // Test 7: Matrix multiplication.
    {
        Matrix3 m;
        m.rotate(Vector3(1.0f, 0.0f, 0.0f), 45.0f);

        if (m * m.transpose() != Matrix3::IDENTITY)
            throw std::runtime_error("DoMatrix3Test() : Test 7 failed");
    }

    // Test 8: Matrix multiplication by scalar.
    {
        Matrix3 expected(
            2.0f, 0.0f, 0.0f,
            0.0f, 2.0f, 0.0f,
            0.0f, 0.0f, 2.0f);

        if (2.0f * Matrix3::IDENTITY != expected)
            throw std::runtime_error("DoMatrix3Test() : Test 8 failed");
    }

    // Test 9: Matrix division by scalar.
    {
        Matrix3 m(
            2.0f, 0.0f, 0.0f,
            0.0f, 2.0f, 0.0f,
            0.0f, 0.0f, 2.0f);

        if (m / 2.0f != Matrix3::IDENTITY)
            throw std::runtime_error("DoMatrix3Test() : Test 9 failed");
    }

    // Test 10: Matrix determinant.
    {
        Matrix3 m;
        m.rotate(Vector3(1.0f, 0.0f, 0.0f), 90.0f);

        // Rotations are orthogonal - i.e., the transpose of a rotation
        // matrix is the same as the inverse of the rotation matrix. Thus
        // an inverse always exists, and so the determinant of the rotation
        // matrix cannot be zero.

        if (Math::closeEnough(m.determinant(), 0.0f))
            throw std::runtime_error("DoMatrix3Test() : Test 10 failed");
    }

    // Test 11: Matrix axes extraction.
    {
        Matrix3 m(
            0.707f, -0.707f, 0.0f,
            1.250f,  1.250f, 0.0f,
            0.0f,    0.0f,   1.0f);

        Vector3 axes[3];
        Vector3 expected[3] = 
        {
            Vector3(0.707f, -0.707f, 0.0f),
            Vector3(1.250f,  1.250f, 0.0f),
            Vector3(0.0f,    0.0f,   1.0f)
        };

        // Part a. Axes extraction.
        m.toAxes(axes[0], axes[1], axes[2]);

        if (axes[0] != expected[0] || axes[1] != expected[1] || axes[2] != expected[2])
            throw std::runtime_error("DoMatrix3Test() : Test 11 Part A failed");

        // Part b. Transposed axes extraction.
        expected[0].set(0.707f, 1.250f, 0.0f);
        expected[1].set(-0.707f, 1.250f, 0.0f);
        expected[2].set(0.0f, 0.0f, 1.0f);

        m.toAxesTransposed(axes[0], axes[1], axes[2]);

        if (axes[0] != expected[0] || axes[1] != expected[1] || axes[2] != expected[2])
            throw std::runtime_error("DoMatrix3Test() : Test 11 Part B failed");
    }

    // Test 12: Matrix Euler conversion.
    {
        float eulerOut[3] = {0.0f};
        float eulerIn[3] = {10.0f, 20.0f, 30.0f};
        Matrix3 m;

        // Create a rotation matrix from an Euler transform, and then
        // extract the original Euler transform from the created rotation
        // matrix.

        m.fromHeadPitchRoll(eulerIn[0], eulerIn[1], eulerIn[2]);
        m.toHeadPitchRoll(eulerOut[0], eulerOut[1], eulerOut[2]);

        if (!Math::closeEnough(eulerOut[0], eulerIn[0]) || !Math::closeEnough(eulerOut[1], eulerIn[1]) || !Math::closeEnough(eulerOut[1], eulerIn[1]))
            throw std::runtime_error("DoMatrix3Test() : Test 12 failed");
    }

    // Test 13: Matrix inverse.
    {
        Matrix3 m;
        m.fromHeadPitchRoll(10.0f, 20.0f, 30.0f);

        if (m * m.inverse() != Matrix3::IDENTITY)
            throw std::runtime_error("DoMatrix3Test() : Test 13 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Matrix4 class. This is not an exhaustive test of the
// Matrix4 class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoMatrix4Test()
{
    // Test 1: Matrix equality.
    {
        Matrix4 m = Matrix4::IDENTITY;

        if (m != Matrix4::IDENTITY)
            throw std::runtime_error("DoMatrix4Test() : Test 1 failed");
    }

    // Test 2: Matrix orientation.
    {
        Matrix4 m;
        Vector3 from, to, result;

        // Case 1: Rotate the x-axis into the x-axis.
        from.set(1.0f, 0.0f, 0.0f);
        to.set(1.0f, 0.0f, 0.0f);
        m.orient(from, to);
        result = from * m;

        if (result != to)
            throw std::runtime_error("DoMatrix4Test() : Test 2 Case 1 failed");

        // Case 2: Rotate the x-axis into the negative x-axis.
        from.set(1.0f, 0.0f, 0.0f);
        to.set(-1.0f, 0.0f, 0.0f);
        m.orient(from, to);
        result = from * m;

        if (result != to)
            throw std::runtime_error("DoMatrix4Test() : Test 2 Case 2 failed");

        // Case 3: Rotate the x-axis into the y-axis.
        from.set(1.0f, 0.0f, 0.0f);
        to.set(0.0f, 1.0f, 0.0f);
        m.orient(from, to);
        result = from * m;

        if (result != to)
            throw std::runtime_error("DoMatrix4Test() : Test 2 Case 3 failed");
    }

    // Test 3: Matrix construction.
    {
        Matrix4 m(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

        if (m != Matrix4::IDENTITY)
            throw std::runtime_error("DoMatrix4Test() : Test 3 failed");
    }

    // Test 4: Matrix addition.
    {
        Matrix4 m1(
            1.0f, 1.0f, 1.0f, 1.0f,
            2.0f, 2.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 3.0f, 3.0f,
            4.0f, 4.0f, 4.0f, 4.0f);

        Matrix4 i = Matrix4::IDENTITY;

        Matrix4 expected(
            2.0f, 1.0f, 1.0f, 1.0f,
            2.0f, 3.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 4.0f, 3.0f,
            4.0f, 4.0f, 4.0f, 5.0f);

        if (m1 + i != expected)
            throw std::runtime_error("DoMatrix4Test() : Test 4 failed");
    }

    // Test 5: Matrix subtraction.
    {
        Matrix4 m1(
            1.0f, 1.0f, 1.0f, 1.0f,
            2.0f, 2.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 3.0f, 3.0f,
            4.0f, 4.0f, 4.0f, 4.0f);

        Matrix4 i = Matrix4::IDENTITY;

        Matrix4 expected(
            0.0f, 1.0f, 1.0f, 1.0f,
            2.0f, 1.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 2.0f, 3.0f,
            4.0f, 4.0f, 4.0f, 3.0f);

        if (m1 - i != expected)
            throw std::runtime_error("DoMatrix4Test() : Test 5 failed");
    }

    // Test 6: Matrix transpose.
    {
        Matrix4 m(
            1.0f, 1.0f, 1.0f, 1.0f,
            2.0f, 2.0f, 2.0f, 2.0f,
            3.0f, 3.0f, 3.0f, 3.0f,
            4.0f, 4.0f, 4.0f, 4.0f);

        Matrix4 expected(
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            1.0f, 2.0f, 3.0f, 4.0f);

        if (m.transpose() != expected)
            throw std::runtime_error("DoMatrix4Test() : Test 6 failed");
    }

    // Test 7: Matrix multiplication.
    {
        Matrix4 m;
        m.rotate(Vector3(1.0f, 0.0f, 0.0f), 45.0f);

        if (m * m.transpose() != Matrix4::IDENTITY)
            throw std::runtime_error("DoMatrix4Test() : Test 7 failed");
    }

    // Test 8: Matrix multiplication by scalar.
    {
        Matrix4 expected(
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 2.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 2.0f);

        if (2.0f * Matrix4::IDENTITY != expected)
            throw std::runtime_error("DoMatrix4Test() : Test 8 failed");
    }

    // Test 9: Matrix division by scalar.
    {
        Matrix4 m(
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 2.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 2.0f);

        if (m / 2.0f != Matrix4::IDENTITY)
            throw std::runtime_error("DoMatrix4Test() : Test 9 failed");
    }

    // Test 10: Matrix determinant.
    {
        Matrix4 m;
        m.rotate(Vector3(1.0f, 0.0f, 0.0f), 90.0f);

        // Rotations are orthogonal - i.e., the transpose of a rotation
        // matrix is the same as the inverse of the rotation matrix. Thus
        // an inverse always exists, and so the determinant of the rotation
        // matrix cannot be zero.

        if (Math::closeEnough(m.determinant(), 0.0f))
            throw std::runtime_error("DoMatrix4Test() : Test 10 failed");
    }

    // Test 11: Matrix axes extraction.
    {
        Matrix4 m(
            0.707f, -0.707f, 0.0f, 0.0f,
            1.250f,  1.250f, 0.0f, 0.0f,
            0.0f,    0.0f,   1.0f, 0.0f,
            0.0f,    0.0f,   0.0f, 1.0f);
        
        Vector3 axes[3];
        Vector3 expected[3] = 
        {
            Vector3(0.707f, -0.707f, 0.0f),
            Vector3(1.250f,  1.250f, 0.0f),
            Vector3(0.0f,    0.0f,   1.0f)
        };

        // Part a. Axes extraction.
        m.toAxes(axes[0], axes[1], axes[2]);

        if (axes[0] != expected[0] || axes[1] != expected[1] || axes[2] != expected[2])
            throw std::runtime_error("DoMatrix4Test() : Test 11 Part A failed");

        // Part b. Transposed axes extraction.
        expected[0].set(0.707f, 1.250f, 0.0f);
        expected[1].set(-0.707f, 1.250f, 0.0f);
        expected[2].set(0.0f, 0.0f, 1.0f);

        m.toAxesTransposed(axes[0], axes[1], axes[2]);

        if (axes[0] != expected[0] || axes[1] != expected[1] || axes[2] != expected[2])
            throw std::runtime_error("DoMatrix4Test() : Test 11 Part B failed");
    }

    // Test 12: Matrix Euler conversion.
    {
        float eulerOut[3] = {0.0f};
        float eulerIn[3] = {10.0f, 20.0f, 30.0f};
        Matrix4 m;

        // Create a rotation matrix from an Euler transform, and then
        // extract the original Euler transform from the created rotation
        // matrix.

        m.fromHeadPitchRoll(eulerIn[0], eulerIn[1], eulerIn[2]);
        m.toHeadPitchRoll(eulerOut[0], eulerOut[1], eulerOut[2]);

        if (!Math::closeEnough(eulerOut[0], eulerIn[0]) || !Math::closeEnough(eulerOut[1], eulerIn[1]) || !Math::closeEnough(eulerOut[1], eulerIn[1]))
            throw std::runtime_error("DoMatrix4Test() : Test 12 failed");
    }

    // Test 13: Matrix inverse.
    {
        Matrix4 m;
        m.fromHeadPitchRoll(10.0f, 20.0f, 30.0f);

        if (m * m.inverse() != Matrix4::IDENTITY)
            throw std::runtime_error("DoMatrix4Test() : Test 13 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the Quaternion class. This is not an exhaustive test of the
// Quaternion class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoQuaternionTest()
{
    // Test 1: Quaternion equality.
    {
        Quaternion q = Quaternion::IDENTITY;

        if (q != Quaternion::IDENTITY)
            throw std::runtime_error("DoQuaternionTest() : Test 1 failed");
    }

    // Test 2: Quaternion addition.
    {
        Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);

        if (q + q != Quaternion(2.0f, 2.0f, 2.0f, 2.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 2 failed");
    }

    // Test 3: Quaternion subtraction.
    {
        Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);

        if (q - q != Quaternion(0.0f, 0.0f, 0.0f, 0.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 3 failed");
    }

    // Test 4: Quaternion multiplication by scalar.
    {
        Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);

        if (2.0f * q != Quaternion(2.0f, 2.0f, 2.0f, 2.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 4 failed");
    }

    // Test 5: Quaternion division by scalar.
    {
        Quaternion q(2.0f, 2.0f, 2.0f, 2.0f);

        if (q / 2.0f != Quaternion(1.0f, 1.0f, 1.0f, 1.0))
            throw std::runtime_error("DoQuaternionTest() : Test 5 failed");
    }

    // Test 6: Quaternion multiplication.
    {
        // Rotate the x-axis 90 degrees about the z-axis so that the
        // x-axis will become the y-axis.

        Vector3 axisIn(1.0f, 0.0f, 0.0f);
        Quaternion pure(0.0f, axisIn.x, axisIn.y, axisIn.z);

        Quaternion rot;
        rot.fromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), 90.0f);

        Quaternion result = rot.conjugate() * pure * rot;
        Vector3 axisOut(result.x, result.y, result.z);

        if (axisOut != Vector3(0.0f, 1.0f, 0.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 6 failed");
    }

    // Test 7: Quaternion conjugate.
    {
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);

        if (q.conjugate() != Quaternion(1.0f, -2.0f, -3.0f, -4.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 7 failed");
    }

    // Test 8: Quaternion axis-angle conversion.
    {
        // Case 1: Angle and axis.

        float degreesIn = 45.0f;
        Vector3 axisIn(0.0f, 1.0f, 0.0f);

        Quaternion q;
        q.fromAxisAngle(axisIn, degreesIn);

        float degreesOut;
        Vector3 axisOut;

        q.toAxisAngle(axisOut, degreesOut);

        if (!Math::closeEnough(degreesOut, degreesIn) || axisOut != axisIn)
            throw std::runtime_error("DoQuaternionTest() : Test 8 Case 1 failed");

        // Case 2: Angle is zero degrees.
        // The axis is irrelevant for this case since there is no rotation occurring.

        degreesIn = 0.0f;
        q.fromAxisAngle(axisIn, degreesIn);
        q.toAxisAngle(axisOut, degreesOut);

        if (!Math::closeEnough(degreesOut, degreesIn))
            throw std::runtime_error("DoQuaternionTest() : Test 8 Case 2 failed");
    }

    // Test 9: Quaternion Euler conversion.
    {
        long eulerIn[3] = {10, 20, 30};
        float eulerOut[3] = {0.0f};
        Quaternion q;

        q.fromHeadPitchRoll(float(eulerIn[0]), float(eulerIn[1]), float(eulerIn[2]));
        q.toHeadPitchRoll(eulerOut[0], eulerOut[1], eulerOut[2]);

        // Quaternion to Euler conversion causes numerical imprecision.
        // Extracting the Euler transform from a quaternion is not a well
        // defined mathematical operation - numerical imprecision can and
        // will result. This test will pass for the values stored in eulerIn.
        // However changing the values may cause this test to fail.

        for (int i = 0; i < 3; ++i)
        {
            if (!Math::closeEnough(eulerOut[i], float(eulerIn[i])))
                throw std::runtime_error("DoQuaternionTest() : Test 9 failed");
        }
    }

    // Test 10: Quaternion magnitude.
    {
        Quaternion q = Quaternion::IDENTITY;

        if (!Math::closeEnough(q.magnitude(), 1.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 10 failed");
    }

    // Test 11: Quaternion normalize.
    {
        Quaternion q(2.0f, 2.0f, 2.0f, 2.0f);
        q.normalize();

        if (!Math::closeEnough(q.magnitude(), 1.0f))
            throw std::runtime_error("DoQuaternionTest() : Test 11 failed");
    }

    // Test 12: Quaternion matrix conversion.
    {
        // Rotate the x-axis 90 degrees about the z-axis so that the
        // x-axis will become the y-axis.

        const Vector3 xAxis(1.0f, 0.0f, 0.0f);
        const Vector3 yAxis(0.0f, 1.0f, 0.0f);
        const Vector3 zAxis(0.0f, 0.0f, 1.0f);
        Quaternion q;

        q.fromAxisAngle(zAxis, 90.0f);

        Matrix4 m = q.toMatrix4();
        Vector3 axisResult = xAxis * m;

        if (axisResult != yAxis)
            throw std::runtime_error("DoQuaternionTest() : Test 12 failed");
    }

    // Test 13: Quaternion point rotation.
    {
        /*
            Some useful quaternions taken from:
            http://www.ogre3d.org/wiki/index.php/Quaternion_and_Rotation_Primer

            w 	        x 	        y 	        z 	         Description
            ---------------------------------------------------------------------------------
            1 	        0 	        0 	        0 	         Identity quaternion, no rotation 
            0 	        1 	        0 	        0 	         180' turn around X axis 
            0 	        0 	        1 	        0 	         180' turn around Y axis 
            0 	        0 	        0 	        1 	         180' turn around Z axis 
            sqrt(0.5) 	sqrt(0.5) 	0 	        0 	         90' rotation around X axis 
            sqrt(0.5) 	0 	        sqrt(0.5) 	0 	         90' rotation around Y axis 
            sqrt(0.5) 	0 	        0 	        sqrt(0.5) 	 90' rotation around Z axis 
            sqrt(0.5) 	-sqrt(0.5) 	0 	        0 	        -90' rotation around X axis 
            sqrt(0.5) 	0 	        -sqrt(0.5) 	0 	        -90' rotation around Y axis 
            sqrt(0.5) 	0 	        0 	        -sqrt(0.5) 	-90' rotation around Z axis
        */

        // Rotate the point at <0,0,20> 180 degrees about the y-axis to give
        // the transformed point <0,0,-20>.

        Vector3 point(0.0f, 0.0f, 20.0f);
        Vector3 expectedPoint(0.0f, 0.0f, -20.0f);
        
        Quaternion pure(0.0f, point.x, point.y, point.z);
        Quaternion rotation(0.0f, 0.0f, 1.0f, 0.0);
        
        Quaternion result = rotation.conjugate() * pure * rotation;
        Vector3 transformedPoint(result.x, result.y, result.z);

        if (transformedPoint != expectedPoint)
            throw std::runtime_error("DoQuaternionTest() : Test 13 failed");
    }

    // Test 14: Quaternion SLERP.
    {
        Quaternion src(sqrtf(0.5f), sqrtf(0.5f), 0.0f, 0.0f);   // 90' rotation around X axis
        Quaternion dest(sqrtf(0.5f), -sqrtf(0.5f), 0.0f, 0.0f); // -90' rotation around X axis

        // Case 1: When t == 0, result == src
        if (Quaternion::slerp(src, dest, 0.0f) != src)
            throw std::runtime_error("DoQuaternionTest() : Test 14 Case 1 failed");

        // Case 2: When t == 1, result == dest
        if (Quaternion::slerp(src, dest, 1.0f) != dest)
            throw std::runtime_error("DoQuaternionTest() : Test 14 Case 2 failed");

        // Case 3: When t == 0.5, result == 0' rotation around X axis (i.e., identity).
        if (Quaternion::slerp(src, dest, 0.5f) != Quaternion::IDENTITY)
            throw std::runtime_error("DoQuaternionTest() : Test 14 Case 3 failed");
    }
}

//-----------------------------------------------------------------------------
// Unit test the MatrixStack class. This is not an exhaustive test of the
// MatrixStack class. However it will test most of the important functions.
//-----------------------------------------------------------------------------

void DoMatrixStackTest()
{
	// Test 1: Create a default MatrixStack object.
	{
		MatrixStack ms;

		if (ms.maxDepth() != MatrixStack::DEFAULT_MAX_STACK_DEPTH)
			throw std::runtime_error("DoMatrixStackTest() : Test 1 failed");
	}

	// Test 2: Create a custom MatrixStack object.
	{
		int maxDepth = 256;
		MatrixStack ms(maxDepth);

		if (ms.maxDepth() != maxDepth)
			throw std::runtime_error("DoMatrixStackTest() : Test 2 failed");
	}

	// Test 3: Load identity matrix.
	{
		MatrixStack ms;

		ms.loadIdentity();

		if (ms.currentMatrix() != Matrix4::IDENTITY)
			throw std::runtime_error("DoMatrixStackTest() : Test 3 failed");
	}

	// Test 4: Load matrix.
	{
		Matrix4 m( 1.0f,  2.0f,  3.0f,  4.0f,
				   5.0f,  6.0f,  7.0f,  8.0f,
				   9.0f, 10.0f, 11.0f, 12.0f,
				  13.0f, 14.0f, 15.0f, 16.0f);

		MatrixStack ms;

		ms.loadMatrix(m);

		if (ms.currentMatrix() != m)
			throw std::runtime_error("DoMatrixStackTest() : Test 4 failed");
	}

	// Test 5: Multiply matrices.
	{
		Matrix4 m1(1.0f, 1.0f, 1.0f, 1.0f,
			       2.0f, 2.0f, 2.0f, 2.0f,
				   3.0f, 3.0f, 3.0f, 3.0f,
				   4.0f, 4.0f, 4.0f, 4.0f);

		Matrix4 m2(1.0f, 2.0f, 3.0f, 4.0f,
			       1.0f, 2.0f, 3.0f, 4.0f,
				   1.0f, 2.0f, 3.0f, 4.0f,
				   1.0f, 2.0f, 3.0f, 4.0f);

		Matrix4 m3 = m1 * m2;

		MatrixStack ms;

		ms.loadMatrix(m1);
		ms.multMatrix(m2);

		if (ms.currentMatrix() != m3)
			throw std::runtime_error("DoMatrixStackTest() : Test 5 failed");
	}

	// Test 6: Stack underflow error.
	{
		MatrixStack ms;
		
		// (a) We should be at the min stack depth.
		
		if (ms.currentDepth() != 0)
			throw std::runtime_error("DoMatrixStackTest() : Test 6a failed");

		// (b) Cause a stack underflow error.

		ms.popMatrix();

		if (ms.lastError() != MatrixStack::ERROR_MATRIX_STACK_UNDERFLOW)
			throw std::runtime_error("DoMatrixStackTest() : Test 6b failed");
	}

	// Test 7: Stack overflow error.
	{
		MatrixStack ms;

		// (a) Make sure we have reached the max stack depth.

		for (unsigned int i = 0; i < ms.maxDepth(); ++i)
			ms.pushMatrix();
		
		if (ms.currentDepth() != ms.maxDepth() - 1)
			throw std::runtime_error("DoMatrixStackTest() : Test 7a failed");

		// (b) Cause a stack overflow error.

		ms.pushMatrix();

		if (ms.lastError() != MatrixStack::ERROR_MATRIX_STACK_OVERFLOW)
			throw std::runtime_error("DoMatrixStackTest() : Test 7b failed");
	}

	// Test 8: Pushing and popping.
	{
		Matrix4 m1(1.0f, 1.0f, 1.0f, 1.0f,
			       1.0f, 1.0f, 1.0f, 1.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,
				   1.0f, 1.0f, 1.0f, 1.0f);

		Matrix4 m2(2.0f, 2.0f, 2.0f, 2.0f,
			       2.0f, 2.0f, 2.0f, 2.0f,
				   2.0f, 2.0f, 2.0f, 2.0f,
				   2.0f, 2.0f, 2.0f, 2.0f);

		MatrixStack ms;

		ms.loadMatrix(m1);
		ms.pushMatrix();
		ms.loadMatrix(m2);

		// (a) The top of the matrix stack now contains matrix m2.

		if (ms.currentMatrix() != m2)
			throw std::runtime_error("DoMatrixStackTest() : Test 8a failed");

		ms.popMatrix();

		// (b) The top of the matrix stack now contains matrix m1.

		if (ms.currentMatrix() != m1)
			throw std::runtime_error("DoMatrixStackTest() : Test 8b failed");
	}
}