using System;
using JsonKnownTypes;
using Newtonsoft.Json;
// ReSharper disable InconsistentNaming
// ReSharper disable UnusedMemberInSuper.Global


namespace JsonSchemas
{
    [JsonConverter(typeof(JsonKnownTypesConverter<j_typed>))]
    public class j_typed
    {
        protected j_typed()
        {
        }

        public virtual bool IsValid()
        {
            if (GetType() == typeof(j_typed)) throw new NotImplementedException(GetType() + "needs IsValid");
            return true;
        }

        public virtual void Execute()
        {
            throw new NotImplementedException(GetType() + "needs Execute");
        }
    }
}