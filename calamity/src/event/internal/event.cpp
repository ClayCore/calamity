#include "event.hpp"

namespace Calamity::EventSystem
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

    const char*
    Event::get_name_from_type(const EventType& type) const
    {
        auto result = "";

        // clang-format off
        switch (type) {
            case EventType::None:                   { result = "None";                }; break;
            // Window handling events                                                        //
            // ----------------------------------------------------------------------------- //
            case EventType::WindowClose:            { result = "WindowClose";         }; break;
            case EventType::WindowResize:           { result = "WindowResize";        }; break;
            case EventType::WindowFocus:            { result = "WindowFocus";         }; break;
            case EventType::WindowLostFocus:        { result = "WindowLostFocus";     }; break;
            case EventType::WindowMoved:            { result = "WindowMoved";         }; break;
            // Resource management                                                           //
            // ----------------------------------------------------------------------------- //
            case EventType::LoadResource:           { result = "LoadResource";        }; break;
            case EventType::FreeResource:           { result = "FreeResource";        }; break;
            // Engine internals                                                              //
            // ----------------------------------------------------------------------------- //
            case EventType::EngineTick:             { result = "EngineTick";          }; break;
            case EventType::EngineUpdate:           { result = "EngineUpdate";        }; break;
            case EventType::EngineRender:           { result = "EngineRender";        }; break;
            // Input handling                                                                //
            // ----------------------------------------------------------------------------- //
            case EventType::KeyPressed:             { result = "KeyPressed";          }; break;
            case EventType::KeyReleased:            { result = "KeyReleased";         }; break;
            case EventType::MouseButtonPressed:     { result = "MouseButtonPressed";  }; break;
            case EventType::MouseButtonReleased:    { result = "MouseButtonReleased"; }; break;
            case EventType::MouseMoved:             { result = "MouseMoved";          }; break;
            case EventType::MouseScrolled:          { result = "MouseScrolled";       }; break;
            // Custom events                                                                 //
            // ----------------------------------------------------------------------------- //
            default:                                { result = "Custom event";        }; break;
        }
        // clang-format on

        return result;
    }

    EventCategory
    Event::get_category_from_type(const EventType& type) const
    {
        auto result = EventCategory::None;

        // clang-format off
        switch (type) {
            case EventType::None:                   { result = EventCategory::None;       }; break;
            // Window handling events                                                            //
            // --------------------------------------------------------------------------------- //
            case EventType::WindowClose:            { result = EventCategory::Window;     }; break;
            case EventType::WindowResize:           { result = EventCategory::Window;     }; break;
            case EventType::WindowFocus:            { result = EventCategory::Window;     }; break;
            case EventType::WindowLostFocus:        { result = EventCategory::Window;     }; break;
            case EventType::WindowMoved:            { result = EventCategory::Window;     }; break;
            // Resource management                                                               //
            // --------------------------------------------------------------------------------- //
            case EventType::LoadResource:           { result = EventCategory::Resource;   }; break;
            case EventType::FreeResource:           { result = EventCategory::Resource;   }; break;
            // Engine internals                                                                  //
            // --------------------------------------------------------------------------------- //
            case EventType::EngineTick:             { result = EventCategory::Engine;     }; break;
            case EventType::EngineUpdate:           { result = EventCategory::Engine;     }; break;
            case EventType::EngineRender:           { result = EventCategory::Engine;     }; break;
            // Input handling                                                                    //
            // --------------------------------------------------------------------------------- //
            case EventType::KeyPressed:             { result = EventCategory::Input;      }; break;
            case EventType::KeyReleased:            { result = EventCategory::Input;      }; break;
            case EventType::MouseButtonPressed:     { result = EventCategory::Input;      }; break;
            case EventType::MouseButtonReleased:    { result = EventCategory::Input;      }; break;
            case EventType::MouseMoved:             { result = EventCategory::Input;      }; break;
            case EventType::MouseScrolled:          { result = EventCategory::Input;      }; break;
            // Custom events                                                                     //
            // --------------------------------------------------------------------------------- //
            default:                                { result = EventCategory::Custom;     }; break;
        }
        // clang-format on

        return result;
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
} // namespace Calamity::EventSystem
