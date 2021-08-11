#include "event.hpp"

namespace EventSystem
{
    // Constructors           //
    // ---------------------- //
    Event::Event()
    {
        this->m_type     = EventType::None;
        this->m_category = EventCategory::None;
    }

    Event::Event(const EventType& type)
    {
        this->m_type     = type;
        this->m_category = this->get_category_from_type(type);
        this->m_name     = this->get_name_from_type(type);
    }

    // Accessors and mutators           //
    // -------------------------------- //
    const char*
    Event::get_name() const
    {
        if (!this->m_name.empty()) {
            return this->m_name.c_str();
        } else {
            return this->get_name_from_type(this->m_type);
        }
    }

    EventType
    Event::get_type() const
    {
        return this->m_type;
    }

    EventCategory
    Event::get_category() const
    {
        return this->m_category;
    }

    const char*
    Event::get_name_from_type(const EventType& type) const
    {
        // clang-format off
        switch (type) {
            case EventType::None:                   { return "None";                };
            // Window handling events                                               //
            // -------------------------------------------------------------------- //
            case EventType::WindowClose:            { return "WindowClose";         };
            case EventType::WindowResize:           { return "WindowResize";        };
            case EventType::WindowFocus:            { return "WindowFocus";         };
            case EventType::WindowLostFocus:        { return "WindowLostFocus";     };
            case EventType::WindowMoved:            { return "WindowMoved";         };
            // Resource management                                                  //
            // -------------------------------------------------------------------- //
            case EventType::LoadResource:           { return "LoadResource";        };
            case EventType::FreeResource:           { return "FreeResource";        };
            // Engine internals                                                     //
            // -------------------------------------------------------------------- //
            case EventType::EngineTick:             { return "EngineTick";          };
            case EventType::EngineUpdate:           { return "EngineUpdate";        };
            case EventType::EngineRender:           { return "EngineRender";        };
            // Input handling                                                       //
            // -------------------------------------------------------------------- //
            case EventType::KeyPressed:             { return "KeyPressed";          };
            case EventType::KeyReleased:            { return "KeyReleased";         };
            case EventType::MouseButtonPressed:     { return "MouseButtonPressed";  };
            case EventType::MouseButtonReleased:    { return "MouseButtonReleased"; };
            case EventType::MouseMoved:             { return "MouseMoved";          };
            case EventType::MouseScrolled:          { return "MouseScrolled";       };
            // Custom events                                                        //
            // -------------------------------------------------------------------- //
            default:                                { return "Custom event";        };
        }
        // clang-format on   
    }

    EventCategory 
    Event::get_category_from_type(const EventType& type) const 
    {
        // clang-format off
        switch (type) {
            case EventType::None:                   { return EventCategory::None;       };
            // Window handling events                                                   //
            // ------------------------------------------------------------------------ //
            case EventType::WindowClose:            { return EventCategory::Window;     };
            case EventType::WindowResize:           { return EventCategory::Window;     };
            case EventType::WindowFocus:            { return EventCategory::Window;     };
            case EventType::WindowLostFocus:        { return EventCategory::Window;     };
            case EventType::WindowMoved:            { return EventCategory::Window;     };
            // Resource management                                                      //
            // ------------------------------------------------------------------------ //
            case EventType::LoadResource:           { return EventCategory::Resource;   };
            case EventType::FreeResource:           { return EventCategory::Resource;   };
            // Engine internals                                                         //
            // ------------------------------------------------------------------------ //
            case EventType::EngineTick:             { return EventCategory::Engine;     };
            case EventType::EngineUpdate:           { return EventCategory::Engine;     };
            case EventType::EngineRender:           { return EventCategory::Engine;     };
            // Input handling                                                           //
            // ------------------------------------------------------------------------ //
            case EventType::KeyPressed:             { return EventCategory::Input;      };
            case EventType::KeyReleased:            { return EventCategory::Input;      };
            case EventType::MouseButtonPressed:     { return EventCategory::Input;      };
            case EventType::MouseButtonReleased:    { return EventCategory::Input;      };
            case EventType::MouseMoved:             { return EventCategory::Input;      };
            case EventType::MouseScrolled:          { return EventCategory::Input;      };
            // Custom events                                                            //
            // ------------------------------------------------------------------------ //
            default:                                { return EventCategory::Custom;     };
        }
        // clang-format on 
    }

    void 
    Event::set_name(const std::string& name) 
    {
        this->m_name = name;
    }

    // Debugging methods           //
    // --------------------------- //
    std::string 
    Event::to_string() const 
    {
        if (!this->m_name.empty()) {
            return this->get_name();
        } else {
            // Get the name from the type
            // TODO: category too?
            return this->get_name_from_type(this->m_type);
        }
    }
} // namespace EventSystem
