using System;
using System.Collections.Generic;
using JsonSchemas.Structs;
using JsonSchemas.Tiles;
using UnityEngine;

// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Tilemap
{
    public class abstract_tilemap : j_typed
    {
        public vector2<int> scale; // : vector2<int>
        public List<base_tile> data; // : base_tile[]

        protected abstract_tilemap()
        {
            
        }

        public virtual Vector3 GetPosition(int x, int y, base_tile tile)
        {
            throw new NotImplementedException("Implement me");
        }
    }
}