#include "object_manager_slots.h"
#include "object_manager_create.h"
#include <string.h>
#include "SMSlib.h"


// enemies
GameObject ObjectManager_enemySlots[MAX_ENEMIES];
u8 ObjectManager_numActiveEnemies;
GameObject* ObjectManager_activeEnemySlots[MAX_ENEMIES];

// effects
GameObject ObjectManager_effects[MAX_EFFECTS];
u8 ObjectManager_numActiveEffects;
u8 ObjectManager_numPendingEffects;
GameObject* ObjectManager_activeEffectsA[MAX_EFFECTS];
GameObject* ObjectManager_activeEffectsB[MAX_EFFECTS];
GameObject** ObjectManager_currentActiveEffects = ObjectManager_activeEffectsA;
GameObject** ObjectManager_pendingEffects = ObjectManager_activeEffectsB;

// player projectiles
GameObject ObjectManager_projectiles[MAX_PROJECTILES];
u8 ObjectManager_numActiveProjectiles;
u8 ObjectManager_numPendingProjectiles;
GameObject* ObjectManager_activeProjectilesA[MAX_PROJECTILES];
GameObject* ObjectManager_activeProjectilesB[MAX_PROJECTILES];
GameObject** ObjectManager_currentActiveProjectiles = ObjectManager_activeProjectilesA;
GameObject** ObjectManager_pendingProjectiles = ObjectManager_activeProjectilesB;

// enemy projectile slots
GameObject ObjectManager_enemyProjectiles[MAX_ENEMY_PROJECTILES];
u8 ObjectManager_numActiveEnemyProjectiles;
u8 ObjectManager_numPendingEnemyProjectiles;
GameObject* ObjectManager_activeEnemyProjectilesA[MAX_ENEMY_PROJECTILES];
GameObject* ObjectManager_activeEnemyProjectilesB[MAX_ENEMY_PROJECTILES];
GameObject** ObjectManager_currentActiveEnemyProjectiles = ObjectManager_activeEnemyProjectilesA;
GameObject** ObjectManager_pendingEnemyProjectiles = ObjectManager_activeEnemyProjectilesB;

GameObject ObjectManager_player;
GameObject ObjectManager_Item;


void ObjectManager_InitSlots(void)
{
	ObjectManager_numActiveEnemies = 0;
	ObjectManager_numActiveEffects = 0;
	ObjectManager_numActiveProjectiles = 0;
	ObjectManager_numActiveEnemyProjectiles = 0;

	ObjectManager_numPendingProjectiles = 0;
	ObjectManager_numPendingEnemyProjectiles = 0;
	ObjectManager_numPendingEffects = 0;
}