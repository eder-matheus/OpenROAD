# Liberty Database (LDB) — Binary Liberty Cache

LDB is an opt-in binary cache for parsed Liberty libraries, surfaced
through OpenSTA. The two-step `write_ldb` → `read_ldb` round-trip
produces the same in-memory state as `read_liberty`, but skips the
Liberty text parse on the cache-load path. Useful when the same
Liberty file is loaded many times (interactive sessions, regression
sweeps, CI runs).

LDB is **opt-in only**: `read_liberty` flow scripts continue to work
unchanged. Existing default flows are untouched.

## Tcl commands

```tcl
# Snapshot a parsed library to a binary .ldb file.
write_ldb library filename

# Restore a library from a .ldb file. Skips the Liberty text parse.
read_ldb [-corner corner] [-min] [-max] [-ignore_source_check] filename
```

`write_ldb` takes the library handle (e.g. `[get_libs name]`) and an
output `.ldb` path. `read_ldb` mirrors `read_liberty`'s `-corner` /
`-min` / `-max` arguments. `-ignore_source_check` skips the
source-staleness comparison so the cache file can be loaded after the
original `.lib` has moved or been deleted.

The on-disk format is version 3, magic `'OSLD'`. It is **not**
portable across endians; same-architecture loads only.

## Typical usage

```tcl
# First run -- parse the Liberty file once, snapshot to .ldb.
read_liberty Nangate45/Nangate45_typ.lib
write_ldb [get_libs NangateOpenCellLibrary] Nangate45_typ.ldb

# Subsequent runs -- load directly from .ldb.
read_ldb -ignore_source_check Nangate45_typ.ldb
```

For multi-corner flows, snapshot each corner separately and reload
with the same `-corner` argument:

```tcl
# Parse + snapshot
define_corners fast typ slow
read_liberty -corner fast Nangate45_fast.lib
read_liberty -corner typ  Nangate45_typ.lib
read_liberty -corner slow Nangate45_slow.lib
write_ldb [get_libs NangateOpenCellLibrary_fast] fast.ldb
write_ldb [get_libs NangateOpenCellLibrary]      typ.ldb
write_ldb [get_libs NangateOpenCellLibrary_slow] slow.ldb

# Reload
define_corners fast typ slow
read_ldb -corner fast -ignore_source_check fast.ldb
read_ldb -corner typ  -ignore_source_check typ.ldb
read_ldb -corner slow -ignore_source_check slow.ldb
```

## Equivalence guarantees

A library loaded via `read_ldb` is functionally indistinguishable from
the same library loaded via `read_liberty`: same cells, ports, timing
arcs, internal_power and leakage_power groups, sequentials,
statetable, port flag bits, and FuncExpr trees. Downstream consumers
(`report_checks`, `report_power`, `repair_design`, CTS, detailed
routing) produce byte-identical output across the two load paths.

The equivalence is verified end-to-end by `test/ldb_benchmark/` —
both per-layer probes (emit / dump / db / report) and full-flow
diffs (final DEF + SPEF + QoR metrics) on real designs across
nangate45, sky130hd, sky130hs, and asap7. See
`test/ldb_benchmark/README.md` for details and for running the suite.

## Limits

- Same-architecture only (no endian conversion in the format).
- One on-disk format version (3). No migration path needed yet — LDB
  has not previously shipped in OpenROAD.
- The companion `Tech::readLiberty` C++/Python facade has no
  `Tech::readLdb` counterpart yet; Python users must invoke
  `tech.getSta().readLibertyCache(...)` directly or use the Tcl
  command via `tech.evalTclString(...)`.
