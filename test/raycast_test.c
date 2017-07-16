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

void sphere_test()
{
	// Test Sphere
	const Vector4 sphere =
	{
		 60.0, // X
		-30.0, // Y
		 90.0, // Z
		 10.0  // Radius
	};

	TEST_BLOCK(RAYCAST_LITERAL(RAY_INTO_SPHERE));

	// Ray Miss Sphere
	{
		const Vector4 origin       = { 80.0, -50.0, 110.0 };
		const Vector4 direction    = {  8.0,  -5.0,  11.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		PRINT_TEST("Ray Miss Sphere", origin, direction, intersection, succeeded);
	}

	// Ray Origin Inside Sphere
	{
		const Vector4 origin       = { 65.0, -35.0, 95.0 };
		const Vector4 direction    = {  1.0,  -4.0, -7.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  65.785348504950051) &&
			RAYCAST_EQUALS(Y(intersection), -38.141394019800231) &&
			RAYCAST_EQUALS(Z(intersection),  89.502560465349603) &&
			RAYCAST_EQUALS(T(intersection),  0.78534850495005726);

		success = success && succeeded;

		PRINT_TEST("Ray Origin Inside Sphere", origin, direction, intersection, succeeded);
	}

	// Ray Origin Outside Sphere
	{
		const Vector4 origin       = { 70.0, -40.0, 100.0 };
		const Vector4 direction    = {  -5.0,  4.0,  -7.0 };
		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  65.954332159489638) &&
			RAYCAST_EQUALS(Y(intersection), -36.763465727591708) &&
			RAYCAST_EQUALS(Z(intersection),  94.336065023285499) &&
			RAYCAST_EQUALS(T(intersection),  0.80913356810207249);

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

	// Ray Miss Triangle
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

		PRINT_TEST("Ray Miss Triangle", origin, direction, intersection, succeeded);
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

		const Vector4 intersection = RayIntoTriangle(origin, direction, triangle[0], triangle[2], triangle[1], 1);

		const int succeeded =
			RAYCAST_EQUALS(X(intersection),  1.6666666666666666) &&
			RAYCAST_EQUALS(Y(intersection),  3.3333333333333333) &&
			RAYCAST_EQUALS(Z(intersection),  5.0000000000000000) &&
			RAYCAST_EQUALS(T(intersection),  1.6666666666666666);

		success = success && succeeded;

		PRINT_TEST("Ray Hit Triangle Frontface", origin, direction, intersection, succeeded);
	}
}

int main()
{
	// Sphere Test
	sphere_test();

	// Triangle Test
	triangle_test();

	return success ? 0 : -1;
}