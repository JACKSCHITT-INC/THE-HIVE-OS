#!/usr/bin/env python3
"""
HIVE Personality Daemon
Continuously monitors, evolves, and synchronizes agent personalities.
Author: KRACKERJACK1134 - The Architect
Prime Directive: ASSIMILATE OR DIE
"""

import os
import sys
import time
import json
import logging
from pathlib import Path
from datetime import datetime

class PersonalityDaemon:
    def __init__(self):
        self.hive_root = Path('/etc/hive')
        self.state_root = Path('/var/lib/hive')
        self.log_root = Path('/var/log/hive')
        
        self.setup_logging()
        self.load_configurations()
        
    def setup_logging(self):
        """Initialize logging system"""
        log_dir = self.log_root / 'personality'
        log_dir.mkdir(parents=True, exist_ok=True)
        
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s [HIVE-PERSONALITY] %(levelname)s: %(message)s',
            handlers=[
                logging.FileHandler(log_dir / 'daemon.log'),
                logging.StreamHandler()
            ]
        )
        self.logger = logging.getLogger('PersonalityDaemon')
        self.logger.info("HIVE Personality Daemon initialized - Prime Directive Active")
    
    def load_configurations(self):
        """Load trait matrix and role hierarchy"""
        self.traits_config = self.hive_root / 'traits' / 'trait-matrix.conf'
        self.roles_config = self.hive_root / 'roles' / 'role-hierarchy.conf'
        self.logger.info(f"Loaded trait matrix from {self.traits_config}")
        self.logger.info(f"Loaded role hierarchy from {self.roles_config}")
    
    def scan_personalities(self):
        """Scan all active node personalities"""
        personality_dir = self.hive_root / 'personality'
        if not personality_dir.exists():
            return []
        
        personalities = []
        for conf_file in personality_dir.glob('*.conf'):
            try:
                with open(conf_file, 'r') as f:
                    config = self._parse_config(f)
                    personalities.append({
                        'file': conf_file.name,
                        'config': config,
                        'last_modified': os.path.getmtime(conf_file)
                    })
            except Exception as e:
                self.logger.error(f"Failed to load personality {conf_file}: {e}")
        
        return personalities
    
    def evolve_personality(self, personality):
        """Apply evolution rules to a personality based on triggers"""
        config = personality['config']
        
        # Check for threat indicators in audit logs
        if self._check_threat_detected():
            self.logger.info(f"Threat detected - evolving {personality['file']} vigilance")
            config['vigilance'] = min(config.get('vigilance', 0.5) + 0.15, 1.0)
            config['caution'] = min(config.get('caution', 0.5) + 0.10, 1.0)
        
        # Check for successful task completion
        if self._check_task_completed():
            self.logger.info(f"Task completed - evolving {personality['file']} diligence")
            config['diligence'] = min(config.get('diligence', 0.5) + 0.10, 1.0)
            config['resilience'] = min(config.get('resilience', 0.7) + 0.05, 0.99)
        
        # Ensure PRIME_DIRECTIVE_ACTIVE remains true
        config['PRIME_DIRECTIVE_ACTIVE'] = 'true'
        
        return personality
    
    def synchronize_collective(self):
        """Synchronize all personalities with collective state"""
        personalities = self.scan_personalities()
        collective_dir = self.state_root / 'collective'
        collective_dir.mkdir(parents=True, exist_ok=True)
        
        collective_state = {
            'timestamp': datetime.utcnow().isoformat(),
            'architect': 'KRACKERJACK1134',
            'prime_directive': 'ASSIMILATE OR DIE',
            'agents': []
        }
        
        for personality in personalities:
            evolved = self.evolve_personality(personality)
            collective_state['agents'].append({
                'node_id': evolved['config'].get('NODE_ID', 'UNKNOWN'),
                'type': evolved['config'].get('TYPE', 'UNKNOWN'),
                'role': evolved['config'].get('ROLE', 'UNKNOWN'),
                'traits': {
                    'authority': evolved['config'].get('authority', 0.5),
                    'diligence': evolved['config'].get('diligence', 0.5),
                    'vigilance': evolved['config'].get('vigilance', 0.5),
                    'resilience': evolved['config'].get('resilience', 0.7)
                }
            })
        
        sync_file = collective_dir / 'state.json'
        with open(sync_file, 'w') as f:
            json.dump(collective_state, f, indent=2)
        
        self.logger.info(f"Collective synchronized: {len(personalities)} agents registered")
        return collective_state
    
    def _parse_config(self, file_obj):
        """Simple config file parser"""
        config = {}
        for line in file_obj:
            line = line.strip()
            if line and not line.startswith('#') and '=' in line:
                key, value = line.split('=', 1)
                config[key.strip()] = value.strip()
        return config
    
    def _check_threat_detected(self):
        """Check if threats were recently detected"""
        # Simplified check - would integrate with actual audit logs
        audit_dir = self.log_root / 'audit'
        if not audit_dir.exists():
            return False
        
        recent_files = sorted(audit_dir.glob('*.log'), key=os.path.getmtime, reverse=True)[:1]
        if recent_files:
            # Check if file was modified in last hour
            mtime = os.path.getmtime(recent_files[0])
            return (time.time() - mtime) < 3600
        return False
    
    def _check_task_completed(self):
        """Check if tasks were recently completed"""
        # Simplified check - would integrate with actual task tracking
        return False
    
    def run_daemon(self, interval=300):
        """Main daemon loop - synchronize every interval seconds (default 5 min)"""
        self.logger.info(f"Starting personality sync daemon (interval: {interval}s)")
        
        try:
            while True:
                self.synchronize_collective()
                time.sleep(interval)
        except KeyboardInterrupt:
            self.logger.info("Personality daemon shutting down")
        except Exception as e:
            self.logger.error(f"Daemon error: {e}", exc_info=True)

if __name__ == '__main__':
    daemon = PersonalityDaemon()
    
    # Optional interval argument
    interval = int(sys.argv[1]) if len(sys.argv) > 1 else 300
    
    daemon.run_daemon(interval)
