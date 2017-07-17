#include "raycast.h"

#include <math.h>
#include <stdio.h>

#define RAYCAST_EPSILON 0.0000001
#define RAYCAST_EQUALS(a,b) (fabs(a - b) < RAYCAST_EPSILON)

#if defined (_MSC_VER)
	#include <Windows.h>

	#define TEXT_COLOR_RED   0x0C
	#define TEXT_COLOR_GREEN 0x0A
	#define TEXT_COLOR_CYAN  0x0B
	#define TEXT_COLOR_WHITE 0x07

	#define SET_TEXT_COLOR(color) do { \
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); \
			SetConsoleTextAttribute(hConsole, color);          \
		} while(0)
#else
	#include <sys/ioctl.h>
	
	#define TEXT_COLOR_RED   "\033[1m\033[31m"
	#define TEXT_COLOR_GREEN "\033[1m\033[32m"
	#define TEXT_COLOR_CYAN  "\033[1m\033[36m"
	#define TEXT_COLOR_WHITE "\033[0m\033[37m"

	#define SET_TEXT_COLOR(color) do { \
			printf(color);             \
		} while(0)
#endif

#define TEST_BLOCK(name) do { \
		SET_TEXT_COLOR(TEXT_COLOR_CYAN);    \
		printf("\n###### "name" ######\n"); \
		SET_TEXT_COLOR(TEXT_COLOR_WHITE);   \
	} while(0) \

#define BEGIN_TEST(result) do {                                     \
		SET_TEXT_COLOR(result ? TEXT_COLOR_GREEN : TEXT_COLOR_RED); \
	} while (0)

#define END_TEST() do {                   \
		SET_TEXT_COLOR(TEXT_COLOR_WHITE); \
	} while (0)

#define PRINT_TEST(name,origin,direction,intersection,result) do {           \
	BEGIN_TEST(result);                                                      \
	printf("\n    "name"\n");                                                \
	printf(																	 \
		"        Origin:       <%lf, %lf, %lf>\n"							 \
		"        Direction:    <%lf, %lf, %lf>\n"							 \
		"        Intersection: <%lf, %lf, %lf, %lf>\n",						 \
		X(origin),       Y(origin),       Z(origin),						 \
		X(direction),    Y(direction),    Z(direction),						 \
		X(intersection), Y(intersection), Z(intersection), T(intersection)); \
	printf("        Result:       %s\n", result ? "SUCCESS" : "FAILURE");    \
	END_TEST();                                                              \
	} while(0)

static int success = 1;

// Stringify
#define RAYCAST_STRINGIFY(x) #x
#define RAYCAST_LITERAL(x) RAYCAST_STRINGIFY(x)

void sphere_test()
{
	// Test Sphere
	const Vector4 sphere =
	{
		10.0, // X
		10.0, // Y
		10.0, // Z
		10.0  // Radius
	};

	TEST_BLOCK(RAYCAST_LITERAL(RAY_INTO_SPHERE));

	// Ray Miss Sphere - No Roots
	{
		const Vector4 origin       = { 20.0, 20.0, 20.0 };
		const Vector4 direction    = {  5.0,  5.0, -5.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Miss Sphere (No Roots)", origin, direction, intersection, succeeded);
	}

	// Ray Miss Sphere - Backshot Cull
	{
		const Vector4 origin       = { 20.0, 20.0, 20.0 };
		const Vector4 direction    = {  5.0,  5.0,  5.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Miss Sphere (Backshot Cull)", origin, direction, intersection, succeeded);
	}

	// Ray Origin Inside Sphere
	{
		const Vector4 origin       = { 12.0, 8.0, 6.0 };
		const Vector4 direction    = {  1.0, 2.0, 3.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection), 15.535462764185549) &&
			RAYCAST_EQUALS(Y(intersection), 15.070925528371099) &&
			RAYCAST_EQUALS(Z(intersection), 16.606388292556648) &&
			RAYCAST_EQUALS(T(intersection),  3.5354627641855498);

		success = success && succeeded;

		PRINT_TEST("Ray Origin Inside Sphere", origin, direction, intersection, succeeded);
	}

	// Ray Origin Outside Sphere
	{
		const Vector4 origin       = {  20.0, 20.0, 20.0 };
		const Vector4 direction    = {  -5.0, -4.0, -3.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection), 14.633249580710800) &&
			RAYCAST_EQUALS(Y(intersection), 15.706599664568639) &&
			RAYCAST_EQUALS(Z(intersection), 16.779949748426478) &&
			RAYCAST_EQUALS(T(intersection),  1.0733500838578400);

		success = success && succeeded;

		PRINT_TEST("Ray Origin Outside Sphere", origin, direction, intersection, succeeded);
	}
}

void triangle_test()
{
	// Test Triangle
	const Vector4 triangle[3] =
	{
		{
			 0.0, // X
			 0.0, // Y
			10.0  // Z
		},
		{
			 0.0, // X
			10.0, // Y
			 0.0  // Z
		},
		{
			10.0, // X
			 0.0, // Y
			 0.0  // Z
		}
	};

	TEST_BLOCK(RAYCAST_LITERAL(RAY_INTO_TRIANGLE));

	// Ray Miss Triangle - Parallel
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = {  1.0, -2.0,  1.0 };
		const Vector4 intersection = RayIntoTriangle(origin, direction, triangle[0], triangle[1], triangle[2], 0);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Miss Triangle (Parallel)", origin, direction, intersection, succeeded);
	}

	// Ray Miss Triangle - Backshot Cull
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = {  5.0,  5.0,  5.0 };
		const Vector4 intersection = RayIntoTriangle(origin, direction, triangle[0], triangle[1], triangle[2], 0);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Miss Triangle (Backshot Cull)", origin, direction, intersection, succeeded);
	}

	// Ray Cull Triangle Backface
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = { -5.0, -4.0, -3.0 };
		const Vector4 intersection = RayIntoTriangle(origin, direction, triangle[0], triangle[1], triangle[2], 1);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Cull Triangle Backface", origin, direction, intersection, succeeded);
	}

	// Ray Hit Triangle Backface
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = { -5.0, -4.0, -3.0 };
		const Vector4 intersection = RayIntoTriangle(origin, direction, triangle[0], triangle[1], triangle[2], 0);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  1.6666666666666666) &&
			RAYCAST_EQUALS(Y(intersection),  3.3333333333333333) &&
			RAYCAST_EQUALS(Z(intersection),  5.0000000000000000) &&
			RAYCAST_EQUALS(T(intersection),  1.6666666666666666);

		success = success && succeeded;

		PRINT_TEST("Ray Hit Triangle Backface", origin, direction, intersection, succeeded);
	}

	// Ray Hit Triangle Frontface
	{
		const Vector4 origin    = { 10.0, 10.0, 10.0 };
		const Vector4 direction = { -5.0, -4.0, -3.0 };

		const Vector4 intersection = RayIntoTriangle(origin, direction, triangle[0], triangle[2], triangle[1], 0);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  1.6666666666666666) &&
			RAYCAST_EQUALS(Y(intersection),  3.3333333333333333) &&
			RAYCAST_EQUALS(Z(intersection),  5.0000000000000000) &&
			RAYCAST_EQUALS(T(intersection),  1.6666666666666666);

		success = success && succeeded;

		PRINT_TEST("Ray Hit Triangle Frontface", origin, direction, intersection, succeeded);
	}
}

void plane_test()
{
	// Test Plane
	const Vector4 vertex = {  5.0,  4.0,  3.0 };
	const Vector4 normal = { -2.0, -3.0, -4.0 };

	TEST_BLOCK(RAYCAST_LITERAL(RAY_INTO_PLANE));

	// Ray Miss Plane
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = {  5.0,  5.0,  5.0 };
		const Vector4 intersection = RayIntoPlane(origin, direction, vertex, normal, 0);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Miss Plane", origin, direction, intersection, succeeded);
	}

	// Ray Cull Plane Backface
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = { -5.0, -5.0, -5.0 };
		const Vector4 intersection = RayIntoPlane(origin, direction, vertex, normal, 1);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Cull Plane Backface", origin, direction, intersection, succeeded);
	}

	// Ray Hit Plane Backface
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = { -5.0, -5.0, -5.0 };
		const Vector4 intersection = RayIntoPlane(origin, direction, vertex, normal, 0);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  3.7777777777777777) &&
			RAYCAST_EQUALS(Y(intersection),  3.7777777777777777) &&
			RAYCAST_EQUALS(Z(intersection),  3.7777777777777777) &&
			RAYCAST_EQUALS(T(intersection),  1.244444444444444);

		success = success && succeeded;

		PRINT_TEST("Ray Hit Plane Backface", origin, direction, intersection, succeeded);
	}

	// Ray Hit Plane Frontface
	{
		const Vector4 origin       = { 10.0, 10.0, 10.0 };
		const Vector4 direction    = { -5.0, -5.0, -5.0 };
		const Vector4 intersection = RayIntoPlane(origin, direction, vertex, normal, 0);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  3.7777777777777777) &&
			RAYCAST_EQUALS(Y(intersection),  3.7777777777777777) &&
			RAYCAST_EQUALS(Z(intersection),  3.7777777777777777) &&
			RAYCAST_EQUALS(T(intersection),  1.244444444444444);

		success = success && succeeded;

		PRINT_TEST("Ray Hit Plane Frontface", origin, direction, intersection, succeeded);
	}
}

// Entry point to the test application
int main()
{
	sphere_test();
	triangle_test();
	plane_test();

	return success ? 0 : -1;
}