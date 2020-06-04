using JsonSchemas.Entities;
using UnityEngine;


namespace MonoBehaviours.Elements
{
    public class UnitBehaviour : MonoBehaviour
    {
        public unit unit;

        public void DrawUnit(unit unit)
        {
            this.unit = unit;
            if (unit.parameters_vector2_int.ContainsKey("position"))
            {
                transform.position = new Vector3(unit.parameters_vector2_int["position"].x, 2, unit.parameters_vector2_int["position"].y);
            }
            else
            {
                transform.position = Vector3.up * 30;
            }
        }
    }
}