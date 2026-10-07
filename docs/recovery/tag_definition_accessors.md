# Tag-definition accessor recovery

Eight formerly commented-out accessors in `tag_group_definitions.cpp` now read
the recovered tag-definition fields. Seven belong to `s_tag_struct_definition`;
the eighth returns the name of an `s_tag_block_definition`.

The local declarations describe only the prefixes needed by these accessors.
Their storage lengths are not claims about the complete engine structure sizes,
and these partial layouts are not exposed as allocation types in the header.

## Evidence

The July 7, 2011 `tag_play` executable and its linker map identify all eight
bodies in `tag_group_definitions.obj`. Every body is eight bytes: the indicated
load into `r3`, followed by `blr`. Offsets below are decimal byte offsets from
`this` (also in `r3`).

| Accessor | July 7 address | Load | Offset | July 11 symbol address |
| --- | --- | --- | ---: | --- |
| `s_tag_struct_definition::get_struct_size` | `0x82B73F38` | `lwz` | 28 | `0x82F4CC58` |
| `s_tag_struct_definition::get_cache_file_struct_size` | `0x82B73F40` | `lwz` | 132 | `0x82F4CC68` |
| `s_tag_struct_definition::get_alignment_bits` | `0x82B73F48` | `lwz` | 36 | `0x82F4CC78` |
| `s_tag_struct_definition::get_runtime_flags` | `0x82B73F58` | `lwz` | 124 | `0x82F4CC98` |
| `s_tag_struct_definition::get_exploded_struct_size` | `0x82B73F78` | `ld` | 80 | `0x82F4CCF8` |
| `s_tag_struct_definition::get_struct_vtable` | `0x82B73F80` | `lwz` | 72 | `0x82F4CD08` |
| `s_tag_struct_definition::get_name` | `0x82B74110` | `lwz` | 4 | `0x82F4CED8` |
| `s_tag_block_definition::get_block_name` | `0x82B746F0` | `lwz` | 4 | `0x82F4D790` |

The return types preserve the existing decorated signatures, including the
64-bit exploded size and the const vtable pointer. The loads have no additional
branches, calls, assertions, or side effects in the July 7 evidence.

## Validation

Verified on 2026-10-06 against upstream `8723dc3d` with Microsoft X360 compiler
`16.00.11886.00` from the repository's configured `compilers_20250725` package:

- The complete translation unit compiles with both `/Od` and `/O2`.
- All eight decorated symbols are defined in both compiler listings.
- The `/O2` instruction sequences agree with the July 7 bodies in mnemonic,
  registers, load width, displacement, and return instruction: 8 equal,
  0 different, 0 unresolved. No symbol/branch normalization is needed for these
  two-instruction bodies.
- The source patch passes `git diff --check`.

From a PowerShell prompt at the repository root, the translation-unit check is:

```powershell
& '<compiler-directory>/cl.exe' /nologo /c /Isrc /Isrc/source `
  '/DNOT_IMPLEMENTED=__assume(0)' '/Dmangled_ppc=(void)' /DNULL=0 `
  /D_XBOX /DWIN32 /D_DEBUG /D_CONSOLE /D_MBCS /GF `
  /O2 /FAs /Fa'<output-directory>/tag_definitions_o2.asm' `
  /Fo'<output-directory>/tag_definitions_o2.obj' `
  src/source/omaha/tag_files/tag_group_definitions.cpp
```

Repeat with `/Od` and separate output filenames. For the optimized comparison,
locate each accessor's `PROC` in the listing and compare its two instructions
with the corresponding eight-byte July 7 body at the address above.

This is recovery and verification against July 7, not proof of matching the
project's July 11 `tag_debug` target. The July 11 symbol table records 16-byte
spans for these functions, but its executable is unavailable for comparison.
The translation unit remains `NonMatching` in `objects.json`; no full-game link
or runtime test is claimed. No game binaries or assets are included.
