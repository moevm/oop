using System.Collections.Generic;
using JsonSchemas;
using JsonSchemas.Entities;
using JsonSchemas.Rules;
using MonoBehaviours.Elements;
using Singletons;
using UnityEngine;


namespace MonoBehaviours.Session
{
    public class GameBehaviour : MonoBehaviour
    {
        public UnitBehaviour UnitPrefab;
        public Transform ParentTransform;
        
        private static GameBehaviour _instance;

        private Dictionary<int, UnitBehaviour> _units;

        private unit_factory _factory; //TODO
        private abstract_rule _rule; //TODO

        private void Awake()
        {
            _instance = this;
            _units = new Dictionary<int, UnitBehaviour>();
            _factory = null;
            _rule = null;
        }
        
        private void Start()
        {
            God.NetworkManager.Send(new in_game_info());
        }

        private void OnDestroy()
        {
            _instance = null;
        }
        
        public static void SetFactory(unit_factory factory)
        {
            if (!_instance) return;
            _instance._factory = factory;
        }
        
        public static void SetRule(abstract_rule rule)
        {
            if (!_instance) return;
            _instance._rule = rule;
        }

        public static void Frame(Dictionary<int, unit> units)
        {
            if (!_instance) return;
            foreach (KeyValuePair<int,unit> unit in units)
            {
                if (!_instance._units.ContainsKey(unit.Key))
                {
                    _instance._units[unit.Key] = Instantiate(_instance.UnitPrefab, Vector3.zero, Quaternion.identity, _instance.ParentTransform);
                }
                _instance._units[unit.Key].DrawUnit(unit.Value);
            }
        }
    }
}