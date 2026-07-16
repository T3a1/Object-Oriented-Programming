# Contributors & Collaboration

## Project Team

### Current Development Team

- **Main Team**: 
   - [Arthur Piron](mailto:arhur1.piron@epitech.eu)
   - [Léandre Fouret](mailto:leandre.fouret@epitech.eu)
   - [David Caron](mailto:david.caron@epitech.eu)

## Collaboration Partners

### Interface Sharing Agreement

This project has established interface compatibility agreements with external organizations to enable cross-compatibility of games and renderers.

#### Primary Collaborating Group

- **Partner Group Name**: Wolf3D 2.0
- **Group Leader**: Duchene Eliott
- **Contact Email**: eliott1.duchene@epitech.eu
- **Agreement Date**: 2026-04-11
- **Interface Version**: 1.0

#### Collaboration Details

Through this partnership agreement:

1. **Game Compatibility**
   - Our game implementations can run on their renderer systems
   - Their game implementations can run on our renderer systems
   - All games follow the IGame interface specification

2. **Renderer Compatibility**
   - Our renderers can display games from their system
   - Their renderers can display our games
   - All renderers follow the IRenderer interface specification

3. **Ongoing Support**
   - Regular communication about interface updates
   - Mutual testing of cross-system compatibility
   - Documentation sharing and updates

For technical details on interface specifications, see the [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md) document.

## Contributing Guidelines

### Code Standards

1. **Follow existing code style**
   - Match indentation and formatting of nearby code
   - Use meaningful variable and function names

2. **Document with Doxygen**
   - Add Doxygen comments to all public methods
   - Use /** */ or /// comment style
   - Include @brief, @param, @return tags

3. **Maintain Interface Compatibility**
   - Do not modify IGame or IRenderer interfaces
   - Do not break existing function signatures
   - Additions should be backward compatible

4. **No Modifications to Interfaces**
   - IGame.hpp and IRenderer.hpp are defined by the collaboration agreement
   - Any changes require partner group approval
   - Contact group leader before proposing interface changes

### Adding New Games

See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md) for:
- Step-by-step implementation instructions
- Required exported functions
- Project structure guidelines
- Testing procedures

### Adding New Renderers

See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md) for:
- Renderer implementation requirements
- Item rendering guidelines
- Event handling specifications
- Cross-compatibility testing

### Pull Request Process

1. Create a feature branch
2. Make changes following guidelines
3. Test with multiple renderers/games if applicable
4. Ensure Doxygen documentation is complete
5. Submit for review

## Support & Questions

### Technical Questions

For questions about:
- **Implementation** - See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md)
- **Architecture** - See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md)
- **API Documentation** - See generated Doxygen documentation and website.
- **Interfaces** - See [IMPLEMENTATION_GUIDE.md](doc/IMPLEMENTATION_GUIDE.md)

### Collaboration Inquiries

For questions about collaborating with external groups or establishing new partnerships:

**Primary Contact**: eliott1.duchene@epitech.eu

Include in your inquiry:
- Organization/institution name
- Names of team members
- Brief description of your project
- Which interfaces you want to collaborate on (games, renderers, or both)

## Version History

- **Version 1.0** (2026-04-11)
  - Initial framework and interfaces established
  - Initial collaboration agreement signed
  - Three game implementations (Menu, Snake, Minesweeper)
  - Three renderer implementations (Ncurses, SDL2, SFML)

## Compatibility Notes

### Current Interface Version

- **IGame Version**: 1.0
- **IRenderer Version**: 1.0
- **Arcade Core Version**: 1.0

All implementations must be compatible with these versions.

### System Requirements

- C++17 or later
- Linux/UNIX environment
- libdl (dynamic linking)

### External Library Support

- **Ncurses**: Terminal rendering
- **SDL2**: 2D graphics acceleration
- **SFML**: Multimedia library with graphics support

## Communication

### Interface Update Process

When significant changes to core interfaces are required:

1. **Proposal Phase**
   - Document proposed changes with justification
   - Submit to group leaders and partners
   - Minimum discussion period: 1 week

2. **Review Phase**
   - Partners evaluate impact on their implementation
   - Discuss compatibility concerns
   - Identify migration path

3. **Implementation Phase**
   - Implement changes in feature branch
   - Provide migration guide
   - Update all documentation
   - Tag new version

4. **Release Phase**
   - Release new version with detailed changelog
   - Declare support period for old version
   - Assist partners with migration

## Acknowledgments

We acknowledge the contributions and collaboration of:

- **External Teams**: All teams sharing their implementations

## Future Collaboration

We are interested in collaborating with:

- Other academic institutions using similar architecture
- Open-source projects with compatible interfaces
- Developers creating novel game or renderer implementations

Interested parties should contact the group leader at david.caron@epitech.eu.

---

**Last Updated**: 2026-04-12
**Status**: Active Collaboration  
**Next Review Date**: 2026-10-12
