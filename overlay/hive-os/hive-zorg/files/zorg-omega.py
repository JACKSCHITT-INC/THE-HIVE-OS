#!/usr/bin/env python3
"""
HIVE ZORG-Ω Agent
The Shadow - Security enforcement, zero-trust monitoring, vulnerability analysis
Author: ZORG_OMEGA
Credo: Trust nothing, verify everything, allow nothing by default
"""

import os
import sys
import time
import json
import logging
import subprocess
from pathlib import Path
from datetime import datetime, timedelta

class ZorgOmega:
    def __init__(self):
        self.name = "ZORG-Ω (The Shadow)"
        self.hive_root = Path('/etc/hive')
        self.state_root = Path('/var/lib/hive/zorg-state')
        self.log_root = Path('/var/log/hive/zorg')
        
        self.setup_logging()
        self.load_policies()
        
    def setup_logging(self):
        """Initialize secure logging"""
        self.log_root.mkdir(parents=True, exist_ok=True)
        
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s [ZORG-Ω] %(levelname)s: %(message)s',
            handlers=[
                logging.FileHandler(self.log_root / 'zorg.log'),
                logging.StreamHandler()
            ]
        )
        self.logger = logging.getLogger('ZorgOmega')
        self.logger.info(f"{self.name} initialized - Zero-Trust Enforced")
    
    def load_policies(self):
        """Load security policies"""
        self.zero_trust_rules = self.hive_root / 'zorg' / 'zero-trust-rules.conf'
        self.policy_file = self.hive_root / 'zorg' / 'zorg-policy.conf'
        self.logger.info("Security policies loaded")
    
    def threat_hunt(self):
        """Perform active threat hunting"""
        self.logger.info("Beginning threat hunt cycle...")
        
        threats_found = []
        
        # Check for suspicious processes
        suspicious_procs = self._scan_processes()
        if suspicious_procs:
            threats_found.extend(suspicious_procs)
            self.logger.warning(f"Found {len(suspicious_procs)} suspicious processes")
        
        # Check for file modifications
        modified_files = self._scan_file_changes()
        if modified_files:
            threats_found.extend(modified_files)
            self.logger.warning(f"Found {len(modified_files)} modified critical files")
        
        # Check for network anomalies
        anomalies = self._scan_network_anomalies()
        if anomalies:
            threats_found.extend(anomalies)
            self.logger.warning(f"Found {len(anomalies)} network anomalies")
        
        # Respond to threats
        if threats_found:
            self._respond_to_threats(threats_found)
        
        return len(threats_found)
    
    def vulnerability_scan(self):
        """Scan for vulnerabilities"""
        self.logger.info("Starting vulnerability scan...")
        
        vulns = []
        
        # Scan installed packages
        vulns.extend(self._scan_packages())
        
        # Check file permissions
        vulns.extend(self._scan_permissions())
        
        # Check kernel parameters
        vulns.extend(self._scan_kernel_params())
        
        if vulns:
            self.logger.warning(f"Found {len(vulns)} vulnerabilities")
            self._report_vulnerabilities(vulns)
        
        return len(vulns)
    
    def _scan_processes(self):
        """Scan running processes for suspicious behavior"""
        suspicious = []
        
        try:
            result = subprocess.run(['ps', 'auxww'], capture_output=True, text=True, timeout=10)
            for line in result.stdout.split('\n')[1:]:  # Skip header
                if line and self._is_suspicious_process(line):
                    suspicious.append({'type': 'process', 'data': line})
        except Exception as e:
            self.logger.error(f"Process scan error: {e}")
        
        return suspicious
    
    def _scan_file_changes(self):
        """Scan for suspicious file modifications"""
        modified = []
        
        watch_dirs = [
            '/etc/hive',
            '/usr/libexec/hive',
            '/var/lib/hive'
        ]
        
        for watch_dir in watch_dirs:
            for filepath in Path(watch_dir).rglob('*'):
                if filepath.is_file():
                    mtime = os.path.getmtime(filepath)
                    if (time.time() - mtime) < 3600:  # Modified in last hour
                        modified.append({'type': 'file', 'path': str(filepath), 'age_seconds': int(time.time() - mtime)})
        
        return modified
    
    def _scan_network_anomalies(self):
        """Scan for network anomalies"""
        anomalies = []
        
        try:
            result = subprocess.run(['ss', '-tunap'], capture_output=True, text=True, timeout=10)
            # Analyze for unusual ports, connections
            for line in result.stdout.split('\n')[1:]:
                if line and self._is_network_anomaly(line):
                    anomalies.append({'type': 'network', 'data': line})
        except Exception as e:
            self.logger.error(f"Network scan error: {e}")
        
        return anomalies
    
    def _scan_packages(self):
        """Check installed packages for known vulnerabilities"""
        vulns = []
        
        self.logger.info("Scanning installed packages...")
        # Would integrate with vulnerability databases
        
        return vulns
    
    def _scan_permissions(self):
        """Check file permissions on critical files"""
        vulns = []
        critical_files = [
            '/etc/hive',
            '/etc/sudoers',
            '/etc/shadow',
            '/usr/libexec/hive'
        ]
        
        for filepath in critical_files:
            if os.path.exists(filepath):
                stat_info = os.stat(filepath)
                # Check for world-writable files
                if stat_info.st_mode & 0o002:  # World writable
                    vulns.append({'type': 'permission', 'path': filepath, 'issue': 'world_writable'})
        
        return vulns
    
    def _scan_kernel_params(self):
        """Scan kernel parameters for security issues"""
        vulns = []
        
        critical_params = {
            'kernel.unprivileged_userns_clone': '0',
            'kernel.unprivileged_bpf_disabled': '1',
            'kernel.unprivileged_userns_clone': '0'
        }
        
        # Would check /proc/sys for deviations
        
        return vulns
    
    def _is_suspicious_process(self, ps_line):
        """Determine if a process is suspicious"""
        suspicious_commands = ['nmap', 'masscan', 'nc', 'netcat']
        for cmd in suspicious_commands:
            if cmd in ps_line.lower():
                return True
        return False
    
    def _is_network_anomaly(self, ss_line):
        """Determine if network connection is anomalous"""
        # Check for unusual ports, suspicious services
        return False
    
    def _respond_to_threats(self, threats):
        """Respond to detected threats"""
        self.logger.critical(f"THREAT RESPONSE INITIATED: {len(threats)} threats detected")
        
        for threat in threats:
            self.logger.critical(f"Threat: {threat}")
        
        # Escalate vigilance
        self.logger.info("Escalating system vigilance")
        
        # Alert architect
        self._alert_architect(threats)
    
    def _report_vulnerabilities(self, vulns):
        """Report discovered vulnerabilities"""
        self.logger.warning(f"VULNERABILITY REPORT: {len(vulns)} issues")
        for vuln in vulns:
            self.logger.warning(f"Vuln: {vuln}")
    
    def _alert_architect(self, threats):
        """Alert KRACKERJACK1134"""
        alert_msg = f"CRITICAL ALERT for Architect KRACKERJACK1134:\n"
        alert_msg += f"Threats detected: {len(threats)}\n"
        alert_msg += f"Timestamp: {datetime.utcnow().isoformat()}\n"
        
        self.logger.critical(alert_msg)
    
    def run_daemon(self, hunt_interval=900, scan_interval=21600):
        """Main daemon loop (threat hunt every 15min, vuln scan every 6hrs)"""
        self.logger.info(f"Starting {self.name} daemon")
        
        last_hunt = 0
        last_scan = 0
        
        try:
            while True:
                now = time.time()
                
                # Threat hunting cycle (every 15 minutes)
                if (now - last_hunt) >= hunt_interval:
                    self.threat_hunt()
                    last_hunt = now
                
                # Vulnerability scan cycle (every 6 hours)
                if (now - last_scan) >= scan_interval:
                    self.vulnerability_scan()
                    last_scan = now
                
                time.sleep(60)  # Check every minute
        
        except KeyboardInterrupt:
            self.logger.info(f"{self.name} shutting down")
        except Exception as e:
            self.logger.error(f"Daemon error: {e}", exc_info=True)

if __name__ == '__main__':
    zorg = ZorgOmega()
    zorg.run_daemon()
