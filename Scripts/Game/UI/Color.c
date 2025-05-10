// Color handling for ARMA Reforger

class Color
{
    protected float r, g, b, a;
    
    void Color(float red = 1.0, float green = 1.0, float blue = 1.0, float alpha = 1.0)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
    
    static Color Red()
    {
        return new Color(1.0, 0.0, 0.0, 1.0);
    }
    
    static Color Green()
    {
        return new Color(0.0, 1.0, 0.0, 1.0);
    }
    
    static Color Blue()
    {
        return new Color(0.0, 0.0, 1.0, 1.0);
    }
    
    static Color White()
    {
        return new Color(1.0, 1.0, 1.0, 1.0);
    }
    
    static Color Black()
    {
        return new Color(0.0, 0.0, 0.0, 1.0);
    }
    
    vector ToVector()
    {
        string vecStr = r + " " + g + " " + b + " " + a;
        return vecStr;
    }
}