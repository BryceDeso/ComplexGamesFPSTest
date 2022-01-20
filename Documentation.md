| Bryce Deshotel|
|:-|
|Computer Programming|
|Complex Game System Documentation|

## Classes:

### PortalGun

   **Discription:**
    The PortalGun class is used to manage the placement, linking, and the inputs used to place portals.

##### Includes:

    Header:
        CoreMinimal.h
        Camera/CameraComponent.h
        Components/CapsuleComponent.h
        Portal.h
        PortalGun.generated.h

    Cpp:
        PortalGun.h
        Components/ActorComponent.h
        Components/InputComponent.h
        GameFramework/Actor.h
        Engine/World.h
        DrawDebugHelpers.h
        Portal.h

##### Variables:

    Name: Portal1_BP
    Type: Portal
    Description: Varaible used to hold the blueprint used for CurrentPortal1.

    Name: Portal2_BP
    Type: Portal
    Description: Varaible used to hold the blueprint used for CurrentPortal2.
   
    Name: Portal1
    Type: Portal*
    Description: Varaible used to hold the object that will be placed into the scene.

    Name: Portal2
    Type: Portal*
    Description: Varaible used to hold the object that will be placed into the scene.

    Name: MainCamera
    Type: CameraCompoent*
    Description: Used to store the main camera that will be used to aim where a portal can be placed.

    Name: TestComponet
    Type: CapsuleComponent* 
    Description: Used in a test to get the capsule component of an object that the portal gun is placed on. Stores the capsule compononet.

    Name: Portal1Placed
    Type: bool
    Description: Used to tell if Portal1 has been placed.

    Name: Portal2Placed
    Type: bool
    Description: Used to tell if Portal2 has been placed.

##### Functions:

    Name: UPortalGun()
    Type: Constructor
    Description: Sets default values for the portal gun.

    Name: GetMainCamera()
    Type: void
    Description: Gets the camera component tagged with "MainCamera" attached to a capsule component.

    Name: TickCompoent(float "Deltatime", ELevelTick "TickType", FActorComponentTickFuntion* "ThisTickFuntion")
    Type: virtual void override
    Description: Called every frame.

    Name: BeginPlay()
    Type: virtual void override
    Description: Called at the start of the game.

    Name: BindToInput()
    Type: void
    Description: Binds the inputs that will be used to place portals.

    Name: MovePortal1()
    Type: void
    Description: Will spawn Portal1 at the impact point of a line trace. If Portal1 has already been placed, it will move Portal1 to the new impact point of the line trace.

    Name: MovePortal2()
    Type: void
    Description: Will spawn Portal2 at the impact point of a line trace. If Portal2 has already been placed, it will move Portal12 to the new impact point of the line trace.

---

### Portal

   **Discription:**
    The Portal class is used to handle how the portal should act when somthing collides with it, such as what happens when an object collides with the portal then teleports to the other portal.

##### Includes:

    Header:
        CoreMinimal.h
        GameFramework/PlayerController.h
        Portal.generated.h
    
    Cpp:
        Portal.h"
        Components/BoxComponent.h
        GameFramework/Character.h
        Components/ArrowComponent.h

##### Varibles:

    Name: Collider
    Type: BoxCollider*
    Description: Holds the portal's collider.

    Name: PortalActive
    Type: bool
    Description: Used to tell if the portal can be used.

    Name: Arrow
    Type: ArrowComponent*
    Description: Used to display an arrow that will point in direction of the portal's facing.

    Name: OtherPortal
    Type: Portal*
    Description: Used to store the second portal that this portal will be linked to.

    Name: TestChar
    Type: Character*
    Description: Used to hold the character that is passing through the portal to enable the portal to rotate it.

##### Funtions:

    Name: APortal()
    Type: Constructor
    Description: Sets the default values of the portal.

    Name: BeginPlay()
    Type: virtual void override
    Description: Called at the start of the game.

    Name: Tick(float "DeltaTime")
    Type: virtual void override
    Description: Called every frame.

    Name: TeleportObject()
    Type: void 
    Description: Teleports an object to the OtherPortal's location if it collides with this portal's collider.

    Name: ReActivatePortal
    Type: void
    Description: After an object teleports and exits it's collider, will then set PortalActive to true.

---

### Portal Wall

   **Discription:**
    The Portal Wall class is used to keep portal placement contatined by only allowing Portals to be place in Portal Walls.

##### Includes:

    Header:
        CoreMinimal.h
        GameFramework/Actor.h
        PortalWall.generated.h
    
    Cpp:
        PortalWall.h
        Components/BoxComponent.h
        Components/ArrowComponent.h
        Components/StaticMeshComponent.h


##### Varibles:

    Name: Collider
    Type: BoxCollider*
    Description: Holds the Portal Wall's collider.


    Name: Arrow
    Type: ArrowComponent*
    Description: Used to display an arrow that will point in direction of the Portal Wall's facing.

##### Funtions:

    Name: APortalWall()
    Type: Contructor
    Description: Sets the default values of a Portal Wall

    Name: BeginPlay()
    Type: virtual void override
    Description: Called when the game begins.

    Name: Tick(float "DeltaTime")
    Type: virtual void override
    Description: Called every frame.