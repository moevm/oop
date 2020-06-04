using JsonKnownTypes;
using JsonSchemas;
using Newtonsoft.Json;


namespace CaxapCommon.Wrappers
{
    public static class JsonManager
    {
        private static readonly JsonKnownTypesConverter<j_typed> Converter = new JsonKnownTypesConverter<j_typed>();
        
        static JsonManager()
        {
            JsonKnownTypesSettingsManager.DefaultDiscriminatorSettings = new JsonDiscriminatorSettings()
            {
                DiscriminatorFieldName = "type",
                UseClassNameAsDiscriminator = true
            };
        }

        public static string Serialize(j_typed typed)
        {
            return JsonConvert.SerializeObject(typed, Converter);
        }

        public static j_typed Deserialize(string package)
        {
            return JsonConvert.DeserializeObject<j_typed>(package);
        }
    }
}