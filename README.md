# ActionRoguelike

**Action Roguelike** is a third-person showcase as instructed by Tom Looman’s “Action Roguelike” course, built with Unreal Engine 5.5 (C++ and Blueprints). It features AI combat, projectiles, action buffs/debuffs (like Burning and Thorns), modular abilities, and a dynamic UI system driven by delegates.

---

##  Key Features

- **Projectile Combat**: Aiming, spread mechanics, and projectile motion.
- **Action System**: Modular actions (like jump, shoot, burning, thorns) derived from a parent class.
- **Ability Effects**: Effects like damage-over-time or damage reflection (Thorns) that apply to actors dynamically.
- **UI via Delegates**: Health changes and actions drive UI updates using event-based architecture.
- **Damage Popups**: Floating damage indicators appear above enemies on hit.
- **AI Behavior**: Simple AI with shooting tasks, damage reactions, and defeat mechanics (Using the behavior tree).
- **Networking Ready**: Set up to work with Unreal’s replication (assuming multiplayer logic).
- **Cooker Safe**: Enemy assets and blueprints are referenced properly for packaged builds.

---

##  Project Structure

ActionRoguelike/
├── Content/ # Unreal project content, Blueprints, assets

├── Source/ActionRoguelike/ # C++ source code

│ ├── Characters/

│ ├── Projectiles/

│ ├── Actions/

│ ├── UI/

│ └── ...

├── ActionRoguelike.uproject

└── README.md

---

##  Setup & Build

1. Clone the repo:

   ```bash
   git clone https://github.com/Bolphunga/ActionRoguelike.git
~~Open ActionRoguelike.uproject in Unreal Engine (UE5.x).~~

~~Let Unreal compile the C++ code and may prompt for building a Visual Studio (or Rider) project.~~

~~Hit Play in the editor to start testing.~~

##  How to Use the Features
- **Projectile Spread**

To customize AI shooting spread:

Modify MaxBulletSpreadDeg on the AI behavior tree task.

Uses VRandCone for natural spread relative to aim direction.

- **Thorns Effect**

When enabled via a chest pickup:

Applies to the player.

On taking damage, reflects a percentage of damage back at the attacker using a delegate-based OnHealthChanged.

- **Damage Number UI**

Triggered directly in OnHealthChanged.

Spawns a floating widget with the damage number.

Self-destroys after animation.


## TLDR:
It's a small map to showcase AI, Unreal's Gameplay Ability System, and other systems.

## Controls 
WASD: Movement
Q: Teleport/Dash Ability
F: Blackhole Ability


##  Common Issues & Debugging Tips
* First hit shows zero damage: Often due to the first hit not applying damage or hitting another component. Check your ApplyHealthChange logic and projectile instigator setup.

* Multiplying delegate calls: Occurs when OnHealthChanged or delegates are bound multiple times without removing old bindings. Use RemoveAll(this) before adding.


- **Contribution**
Bugs: If you find bugs—or encounter odd behaviors—please open an issue.

Improvements: Interested in new effects, UI improvements, or optimization features? PRs are welcome!
