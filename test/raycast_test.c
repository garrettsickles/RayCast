#include <stdio.h>

#include "ray.h"
#include "platform.h"

#include <math.h>

#define EPSILON 0.0000001
#define EQUALS(a,b) (fabs(a - b) < EPSILON)

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

	printf
	(
		LITERAL(RAY_INTO_SPHERE)
		"\n"
	);

	// Ray-Sphere Miss
	{
		const Vector4 origin    = { 80.0, -50.0, 110.0 };
		const Vector4 direction = {  8.0,  -5.0,  11.0 };

		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		printf
		(
			"\n    Ray Miss Sphere\n"
		);

		printf
		(
			"        Origin:       <%lf, %lf, %lf>\n"
			"        Direction:    <%lf, %lf, %lf>\n"
			"        Intersection: <%lf, %lf, %lf, %lf>\n",
			X(origin),       Y(origin),       Z(origin),
			X(direction),    Y(direction),    Z(direction),
			X(intersection), Y(intersection), Z(intersection), T(intersection)
		);

		const int succeeded =
			X(intersection) != X(intersection) &&
			Y(intersection) != Y(intersection) &&
			Z(intersection) != Z(intersection) &&
			T(intersection) == INFINITY;

		success = success && succeeded;

		printf
		(
			"        Result:       %s\n",
			succeeded ? "SUCCESS" : "FAILURE"
		);
	}

	// Ray Inside Sphere
	{
		const Vector4 origin    = { 65.0, -35.0, 95.0 };
		const Vector4 direction = {  1.0,  -4.0, -7.0 };

		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		printf
		(
			"\n    Ray Inside Sphere\n"
		);

		printf
		(
			"        Origin:       <%lf, %lf, %lf>\n"
			"        Direction:    <%lf, %lf, %lf>\n"
			"        Intersection: <%lf, %lf, %lf, %lf>\n",
			X(origin),       Y(origin),       Z(origin),
			X(direction),    Y(direction),    Z(direction),
			X(intersection), Y(intersection), Z(intersection), T(intersection)
		);

		const int succeeded =
			EQUALS(X(intersection),  65.785348504950051) &&
			EQUALS(Y(intersection), -38.141394019800231) &&
			EQUALS(Z(intersection),  89.502560465349603) &&
			EQUALS(T(intersection),  0.78534850495005726);

		success = success && succeeded;

		printf
		(
			"        Result:       %s\n",
			succeeded ? "SUCCESS" : "FAILURE"
		);
	}

	// Ray Outside Sphere
	{
		const Vector4 origin    = { 70.0, -40.0, 100.0 };
		const Vector4 direction = {  -5.0,  4.0,  -7.0 };

		const Vector4 intersection = RayIntoSphere(origin, direction, sphere);

		printf
		(
			"\n    Ray Outside Sphere\n"
		);

		printf
		(
			"        Origin:       <%lf, %lf, %lf>\n"
			"        Direction:    <%lf, %lf, %lf>\n"
			"        Intersection: <%lf, %lf, %lf, %lf>\n",
			X(origin),       Y(origin),       Z(origin),
			X(direction),    Y(direction),    Z(direction),
			X(intersection), Y(intersection), Z(intersection), T(intersection)
		);

		const int succeeded =
			EQUALS(X(intersection),  65.954332159489638) &&
			EQUALS(Y(intersection), -36.763465727591708) &&
			EQUALS(Z(intersection),  94.336065023285499) &&
			EQUALS(T(intersection),  0.80913356810207249);

		success = success && succeeded;

		printf
		(
			"        Result:       %s\n",
			succeeded ? "SUCCESS" : "FAILURE"
		);

	}
}

int main()
{
	// Sphere Test
	sphere_test();
	return success ? 0 : -1;
}