// Math.c - Math utility functions for ARMA Reforger
// This file provides common math utilities and functions

/**
 * @brief Math utility class
 */
class Math
{
    // Constants
    static const float PI = 3.14159265359;
    static const float DEG2RAD = 0.0174532925;
    static const float RAD2DEG = 57.2957795131;
    static const float EPSILON = 0.000001;
    
    /**
     * @brief Get the minimum of two values
     * @param a First value
     * @param b Second value
     * @return The smaller value
     */
    static float Min(float a, float b)
    {
        return (a < b) ? a : b;
    }
    
    /**
     * @brief Get the minimum of two integer values
     * @param a First value
     * @param b Second value
     * @return The smaller value
     */
    static int Min(int a, int b)
    {
        return (a < b) ? a : b;
    }
    
    /**
     * @brief Get the maximum of two values
     * @param a First value
     * @param b Second value
     * @return The larger value
     */
    static float Max(float a, float b)
    {
        return (a > b) ? a : b;
    }
    
    /**
     * @brief Get the maximum of two integer values
     * @param a First value
     * @param b Second value
     * @return The larger value
     */
    static int Max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    
    /**
     * @brief Clamp a value between min and max
     * @param value The value to clamp
     * @param min Minimum value
     * @param max Maximum value
     * @return The clamped value
     */
    static float Clamp(float value, float min, float max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    /**
     * @brief Clamp an integer value between min and max
     * @param value The value to clamp
     * @param min Minimum value
     * @param max Maximum value
     * @return The clamped value
     */
    static int Clamp(int value, int min, int max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    /**
     * @brief Linearly interpolate between two values
     * @param a Start value
     * @param b End value
     * @param t Interpolation factor (0-1)
     * @return The interpolated value
     */
    static float Lerp(float a, float b, float t)
    {
        return a + (b - a) * Clamp(t, 0.0, 1.0);
    }
    
    /**
     * @brief Calculate the absolute value
     * @param value The input value
     * @return The absolute value
     */
    static float Abs(float value)
    {
        return (value >= 0.0) ? value : -value;
    }
    
    /**
     * @brief Calculate the absolute value of an integer
     * @param value The input value
     * @return The absolute value
     */
    static int Abs(int value)
    {
        return (value >= 0) ? value : -value;
    }
    
    /**
     * @brief Calculate the sine of an angle
     * @param angle The angle in radians
     * @return The sine value
     */
    static float Sin(float angle)
    {
        // This would call the engine's sin function
        return 0.0;  // Placeholder
    }
    
    /**
     * @brief Calculate the cosine of an angle
     * @param angle The angle in radians
     * @return The cosine value
     */
    static float Cos(float angle)
    {
        // This would call the engine's cos function
        return 0.0;  // Placeholder
    }
    
    /**
     * @brief Calculate the tangent of an angle
     * @param angle The angle in radians
     * @return The tangent value
     */
    static float Tan(float angle)
    {
        // This would call the engine's tan function
        return 0.0;  // Placeholder
    }
    
    /**
     * @brief Convert degrees to radians
     * @param degrees The angle in degrees
     * @return The angle in radians
     */
    static float DegToRad(float degrees)
    {
        return degrees * DEG2RAD;
    }
    
    /**
     * @brief Convert radians to degrees
     * @param radians The angle in radians
     * @return The angle in degrees
     */
    static float RadToDeg(float radians)
    {
        return radians * RAD2DEG;
    }
    
    /**
     * @brief Check if two float values are approximately equal
     * @param a First value
     * @param b Second value
     * @param epsilon Tolerance (default is EPSILON)
     * @return True if approximately equal, false otherwise
     */
    static bool Approximately(float a, float b, float epsilon = EPSILON)
    {
        return Abs(a - b) < epsilon;
    }
    
    /**
     * @brief Round a float to the nearest integer
     * @param value The value to round
     * @return The rounded value
     */
    static int Round(float value)
    {
        return (value >= 0.0) ? int(value + 0.5) : int(value - 0.5);
    }
    
    /**
     * @brief Calculate the square root
     * @param value The input value
     * @return The square root
     */
    static float Sqrt(float value)
    {
        // This would call the engine's sqrt function
        return 0.0;  // Placeholder
    }
    
    /**
     * @brief Calculate the power
     * @param base The base value
     * @param exponent The exponent
     * @return The result
     */
    static float Pow(float base, float exponent)
    {
        // This would call the engine's pow function
        return 0.0;  // Placeholder
    }
}

/**
 * @brief Vector class for 3D coordinates
 */
class vector
{
    // X, Y, Z components
    float X;
    float Y;
    float Z;
    
    // Constructor
    void vector(float x = 0.0, float y = 0.0, float z = 0.0)
    {
        X = x;
        Y = y;
        Z = z;
    }
    
    /**
     * @brief Array access operator
     * @param index The index (0 for X, 1 for Y, 2 for Z)
     * @return The component value
     */
    float operator[](int index)
    {
        switch (index)
        {
            case 0: return X;
            case 1: return Y;
            case 2: return Z;
            default: return 0.0;
        }
    }
    
    /**
     * @brief Vector addition
     * @param other The other vector
     * @return The result vector
     */
    vector operator+(vector other)
    {
        return Vector(X + other.X, Y + other.Y, Z + other.Z);
    }
    
    /**
     * @brief Vector subtraction
     * @param other The other vector
     * @return The result vector
     */
    vector operator-(vector other)
    {
        return Vector(X - other.X, Y - other.Y, Z - other.Z);
    }
    
    /**
     * @brief Vector scalar multiplication
     * @param scalar The scalar value
     * @return The result vector
     */
    vector operator*(float scalar)
    {
        return Vector(X * scalar, Y * scalar, Z * scalar);
    }
    
    /**
     * @brief Vector scalar division
     * @param scalar The scalar value
     * @return The result vector
     */
    vector operator/(float scalar)
    {
        if (Math.Abs(scalar) < Math.EPSILON)
            return Vector(0.0, 0.0, 0.0);
            
        float invScalar = 1.0 / scalar;
        return Vector(X * invScalar, Y * invScalar, Z * invScalar);
    }
    
    /**
     * @brief Vector dot product
     * @param other The other vector
     * @return The dot product
     */
    float Dot(vector other)
    {
        return X * other.X + Y * other.Y + Z * other.Z;
    }
    
    /**
     * @brief Vector cross product
     * @param other The other vector
     * @return The cross product vector
     */
    vector Cross(vector other)
    {
        return Vector(
            Y * other.Z - Z * other.Y,
            Z * other.X - X * other.Z,
            X * other.Y - Y * other.X
        );
    }
    
    /**
     * @brief Calculate the vector length squared
     * @return The length squared
     */
    float LengthSq()
    {
        return X * X + Y * Y + Z * Z;
    }
    
    /**
     * @brief Calculate the vector length
     * @return The length
     */
    float Length()
    {
        return Math.Sqrt(LengthSq());
    }
    
    /**
     * @brief Normalize the vector
     * @return The normalized vector
     */
    vector Normalize()
    {
        float length = Length();
        if (length < Math.EPSILON)
            return Vector(0.0, 0.0, 0.0);
            
        float invLength = 1.0 / length;
        return Vector(X * invLength, Y * invLength, Z * invLength);
    }
    
    /**
     * @brief Calculate the distance squared to another vector
     * @param other The other vector
     * @return The distance squared
     */
    float DistanceSq(vector other)
    {
        float dx = X - other.X;
        float dy = Y - other.Y;
        float dz = Z - other.Z;
        return dx * dx + dy * dy + dz * dz;
    }
    
    /**
     * @brief Calculate the distance to another vector
     * @param other The other vector
     * @return The distance
     */
    float Distance(vector other)
    {
        return Math.Sqrt(DistanceSq(other));
    }
    
    /**
     * @brief Convert to string
     * @return String representation of the vector
     */
    string ToString()
    {
        return string.Format("<%1, %2, %3>", X, Y, Z);
    }
}

// Convenience function for creating a vector
vector Vector(float x = 0.0, float y = 0.0, float z = 0.0)
{
    return new vector(x, y, z);
}