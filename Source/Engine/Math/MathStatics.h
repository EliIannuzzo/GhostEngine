#pragma once

namespace Math
{
	static constexpr float PI					= 3.1415926535897932f;
	static constexpr float SMALL_NUMBER			= 1.e-8f;
	static constexpr float KINDA_SMALL_NUMBER	= 1.e-4f;
	static constexpr float BIG_NUMBER			= 3.4e+38f;
	static constexpr float EULERS_NUMBER		= 2.71828182845904523536f;
	static constexpr float UE_GOLDEN_RATIO		= 1.6180339887498948482045868343656381f;	/* Also known as divine proportion, golden mean, or golden section - related to the Fibonacci Sequence = (1 + sqrt(5)) / 2 */
	static constexpr float FLOAT_NON_FRACTIONAL = 8388608.f; /* All single-precision floating point numbers greater than or equal to this have no fractional value. */

	// Aux constants.
	static constexpr float INV_PI				= 0.31830988618f;
	static constexpr float HALF_PI				= 1.57079632679f;

	// Common square roots
	static constexpr float SQRT_2				= 1.4142135623730950488016887242097f;
	static constexpr float SQRT_3				= 1.7320508075688772935274463415059f;
	static constexpr float INV_SQRT_2			= 0.70710678118654752440084436210485f;
	static constexpr float INV_SQRT_3			= 0.57735026918962576450914878050196f;
	static constexpr float HALF_SQRT_2			= 0.70710678118654752440084436210485f;
	static constexpr float HALF_SQRT_3			= 0.86602540378443864676372317075294f;

	//
	// Magic numbers for numerical precision.
	//
	static constexpr float THRESH_POINT_ON_PLANE			= (0.10f);			/* Thickness of plane for front/back/inside test */
	static constexpr float THRESH_POINT_ON_SIDE				= (0.20f);			/* Thickness of polygon side's side-plane for point-inside/outside/on side test */
	static constexpr float THRESH_POINTS_ARE_SAME			= (0.00002f);		/* Two points are same if within this distance */
	static constexpr float THRESH_POINTS_ARE_NEAR			= (0.015f);			/* Two points are near if within this distance and can be combined if imprecise math is ok */
	static constexpr float THRESH_NORMALS_ARE_SAME			= (0.00002f);		/* Two normal points are same if within this distance */
	static constexpr float THRESH_UVS_ARE_SAME				= (0.0009765625f);	/* Two UV are same if within this threshold (1.0f/1024f) */
																				/* Making this too large results in incorrect CSG classification and disaster */
	static constexpr float THRESH_VECTORS_ARE_NEAR			= (0.0004f);		/* Two vectors are near if within this distance and can be combined if imprecise math is ok */
																				/* Making this too large results in lighting problems due to inaccurate texture coordinates */
	static constexpr float THRESH_SPLIT_POLY_WITH_PLANE		= (0.25f);			/* A plane splits a polygon in half */
	static constexpr float THRESH_SPLIT_POLY_PRECISELY		= (0.01f);			/* A plane exactly splits a polygon */
	static constexpr float THRESH_ZERO_NORM_SQUARED			= (0.0001f);		/* Size of a unit normal that is considered "zero", squared */
	static constexpr float THRESH_NORMALS_ARE_PARALLEL		= (0.999845f);		/* Two unit vectors are parallel if abs(A dot B) is greater than or equal to this. This is roughly cosine(1.0 degrees). */
	static constexpr float THRESH_NORMALS_ARE_ORTHOGONAL	= (0.017455f);		/* Two unit vectors are orthogonal (perpendicular) if abs(A dot B) is less than or equal this. This is roughly cosine(89.0 degrees). */
	
	static constexpr float THRESH_VECTOR_NORMALIZED			= (0.01f);			/** Allowed error for a normalized vector (against squared magnitude) */
	static constexpr float THRESH_QUAT_NORMALIZED			= (0.01f);			/** Allowed error for a normalized quaternion (against squared magnitude) */
}