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

void PrintVector(const char *label, const Vector2 &v);
void PrintVector(const char *label, const Vector3 &v);
void PrintMatrix(const char *label, const Matrix4 &m);
void PrintQuaternion(const char *label, const Quaternion &q);
void PrintPlane(const char *label, const Plane &p);
void PrintVectors(const Vector2 &result, const Vector2 &expected);
void PrintVectors(const Vector3 &result, const Vector3 &expected);
void PrintMatrices(const Matrix4 &result, const Matrix4 &expected);
void PrintQuaternions(const Quaternion &result, const Quaternion &expected);
void PrintPlanes(const Plane &result, const Plane &expected);

//-----------------------------------------------------------------------------
// This application will test the math library.
// Testing will stop when the first error is encountered.
//-----------------------------------------------------------------------------

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout << std::setprecision(12);

    try
    {
        TestMathCore();
        TestMathCollision();

        std::cout << "mathlib: all tests passed" << std::endl;
    }
    catch (std::runtime_error &e)
    {
        std::cout << "mathlib: " << e.what() << std::endl;
    }

    std::cout << "Press enter to continue";
    std::cin.get();

    return 0;
}

//-----------------------------------------------------------------------------
// Diagnostic functions.
//-----------------------------------------------------------------------------

void PrintVector(const char *label, const Vector2 &v)
{
    std::cout << label << std::endl;
    std::cout << "[x,y] = [ " << v.x << ", " << v.y << " ]" << std::endl;
}

void PrintVector(const char *label, const Vector3 &v)
{
    std::cout << label << std::endl;
    std::cout << "[x,y,z] = [ " << v.x << ", " << v.y << ", " << v.z 
        << " ]" << std::endl;
}

void PrintMatrix(const char *label, const Matrix4 &m)
{
    std::cout << label << std::endl;

    for (int i = 0; i < 4; ++i)
    {
        std::cout << "[ " << m[i][0] << ' ' << m[i][1] << ' ' << m[i][2]
            << ' ' << m[i][3] << ']' << std::endl;
    }
}

void PrintQuaternion(const char *label, const Quaternion &q)
{
    std::cout << label << std::endl;
    std::cout << "[w,x,y,z] = [" << q.w << ", " << q.x << ", " << q.y 
        << ", " << q.z << "]" << std::endl; 
}

void PrintPlane(const char *label, const Plane &p)
{
    std::cout << label << std::endl;
    std::cout << "[a,b,c,d] = [" << p.normal().x << ", " << p.normal().y
        << ", " << p.normal().z << ", " << p.d << "]" << std::endl; 
}

void PrintVectors(const Vector2 &result, const Vector2 &expected)
{
    PrintVector("vector result:", result);
    PrintVector("\nvector expected:", expected);
    std::cout << std::endl;
}

void PrintVectors(const Vector3 &result, const Vector3 &expected)
{
    PrintVector("vector result:", result);
    PrintVector("\nvector expected:", expected);
    std::cout << std::endl;
}

void PrintMatrices(const Matrix4 &result, const Matrix4 &expected)
{
    PrintMatrix("matrix result:", result);
    PrintMatrix("\nmatrix expected:", expected);
    std::cout << std::endl;
}

void PrintQuaternions(const Quaternion &result, const Quaternion &expected)
{
    PrintQuaternion("quaternion result:", result);
    PrintQuaternion("\nquaternion expected:", expected);
    std::cout << std::endl;
}

void PrintPlanes(const Plane &result, const Plane &expected)
{
    PrintPlane("plane result:", result);
    PrintPlane("\nplane expected:", expected);
    std::cout << std::endl;
}