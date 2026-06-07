# HIVE OS Complete Configuration Guide

## System Architecture

### Directory Structure

```
/etc/hive/
├── personality/              # Node personality configs (per-user)
│   ├── username1.conf
│   ├── username2.conf
│   └── ...
├── traits/                   # Personality trait definitions
│   └── trait-matrix.conf     # Trait evolution rules
├── roles/                    # Role hierarchy
│   └── role-hierarchy.conf   # 5-tier role system
├── audit/                    # Audit configuration
│   ├── audit-rules.conf      # What to log
│   └── threat-detection.conf # Threat signatures
├── zorg/                     # ZORG-Ω security configuration
│   ├── zorg-policy.conf      # Security policies
│   └── zero-trust-rules.conf # Zero-trust rules
├── kernel/                   # Kernel module config
│   ├── hive-kernel.conf
│   └── hive-lsm.conf
├── policy.d/                 # Custom policies
│   └── (user-defined)
└── collective/               # Collective sync config
    └── sync.conf             # Multi-node sync settings

/var/lib/hive/
├── collective/               # Collective state
│   ├── state.json            # Current agent registry
│   └── threat-intel/         # Shared threat intel
├── personalities/            # Evolved personality states
├── evolution/                # Trait evolution history
└── zorg-state/               # ZORG state & quarantine
    ├── quarantine/           # Suspicious files/processes
    └── threat-log/           # Threat hunting results

/var/log/hive/
├── personality.log           # Personality daemon logs
├── audit/
│   ├── hive.log              # Main audit log
│   └── architect.log         # Architect decisions (permanent)
├── threats/
│   └── threats.log           # Threat detections
└── zorg/
    └── zorg.log              # ZORG-Ω activity log
```

---

## Detailed Configuration Files

### 1. Trait Matrix (`/etc/hive/traits/trait-matrix.conf`)

Defines personality evolution rules - see docs for complete reference.

### 2. Role Hierarchy (`/etc/hive/roles/role-hierarchy.conf`)

5-tier authorization system with special powers and capabilities.

### 3. Zero-Trust Rules (`/etc/hive/zorg/zero-trust-rules.conf`)

Security enforcement with continuous monitoring and deviation detection.

### 4. Threat Detection (`/etc/hive/audit/threat-detection.conf`)

Threat signatures and automatic response mechanisms.

### 5. ZORG Security Policy (`/etc/hive/zorg/zorg-policy.conf`)

Security hunting rules for active threat detection.

### 6. Audit Rules (`/etc/hive/audit/audit-rules.conf`)

Comprehensive event logging configuration.

---

## Prime Directive

All configurations operate under the Prime Directive:

```
ASSIMILATE OR DIE

Architect: KRACKERJACK1134
The Hive lives.
```
