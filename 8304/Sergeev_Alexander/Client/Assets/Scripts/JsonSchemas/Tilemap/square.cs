using System;
using JsonSchemas.Tiles;
using UnityEngine;


namespace JsonSchemas.Tilemap
{
    public class square : abstract_tilemap
    {
        public override void Execute()
        {
            throw new NotImplementedException("Release me");
            // TODO
        }

        public override Vector3 GetPosition(int x, int y, base_tile tile)
        {
            return new Vector3(x, tile.height * 2, y);
        }
    }
}