using System.Collections.Generic;
using GuiConcreteComponents.Session;
using JsonSchemas.Entities;
using JsonSchemas.Rules;
using JsonSchemas.Structs;
using JsonSchemas.Tilemap;
using MonoBehaviours.Session;

// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Game
{
    public class abstract_game : j_typed {
        public unit_factory factory;
        public abstract_rule rule;
        public Dictionary<int, unit> units;
        public Dictionary<int, player> players;
        public abstract_tilemap tilemap;

        protected abstract_game()
        {
        }
        
        public override void Execute()
        {
            if (factory != null)
            {
                GameBehaviour.SetFactory(factory);
            }
            if (rule != null)
            {
                GameBehaviour.SetRule(rule);
            }
            if (units != null)
            {
                GameBehaviour.Frame(units);
            }
            if (players != null)
            {
                PlayersScrollList.DrawScrollList(players);
            }
            if (tilemap != null)
            {
                TilemapBehaviour.DrawTilemap(tilemap);
            }
            // TODO
        }
    }
}