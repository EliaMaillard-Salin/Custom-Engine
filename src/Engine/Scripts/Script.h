#ifndef ENGINE_SCRIPT_H_INCLUDED
#define ENGINE_SCRIPT_H_INCLUDED

#include "define.h"


namespace Engine { class Script; }
class Engine::Script
{
protected:
    static uint16 const Tag = 0;
    virtual uint16 GetTag() = 0;
    
    Script() = default;
    virtual ~Script() = 0;

    virtual void Start() = 0;
    virtual void Awake() = 0;

    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
    virtual void LateUpdate() = 0;

    virtual void Sleep() = 0;
    virtual void End() = 0;

    // Active State
    [[nodiscard]] bool IsActive() const; // Not as easy as it seems (it isn't just return m_active) [CALL ME]
    void SetActive( bool active );
    void Activate();
    void Deactivate();

private:
    bool m_created = false; // Whether this Script has been created yet.
    bool m_active = true;   // Whether this Script is active and should be processed.
    bool m_removed = false; // Whether this Script has been removed (gameplay) but not deleted (engine) yet.
    
    friend class ScriptSystem;
};


#endif