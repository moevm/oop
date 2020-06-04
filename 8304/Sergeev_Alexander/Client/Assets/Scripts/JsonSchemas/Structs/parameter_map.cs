using System.Collections.Generic;
// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Structs
{
    public class parameter_map
    {
        public Dictionary<string, bool> parameters_bool; // : map<string, bool>
        public Dictionary<string, int> parameters_int; // : map<string, int>
        public Dictionary<string, float> parameters_float; // : map<string, float>
        public Dictionary<string, string> parameters_string; // : map<string, string>
        public Dictionary<string, vector2<int>> parameters_vector2_int; // : map<string, vector2<int>>
        public Dictionary<string, vector2<float>> parameters_vector2_float; // : map<string, vector2<float>>
        public Dictionary<string, List<vector2<int>>> parameters_list_vector2; // : map<string, std::list<vector2<int>>>
    }
}