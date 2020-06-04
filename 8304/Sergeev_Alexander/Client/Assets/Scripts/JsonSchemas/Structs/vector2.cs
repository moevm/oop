// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Structs
{
    public class vector2<T>
    {
        public T x; // : T where T : new()
        public T y; // : T where T : new()

        public vector2(T x, T y)
        {
            this.x = x;
            this.y = y;
        }
    }
}