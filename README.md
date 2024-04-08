# Memstresstest

This program allocates memory according to specified configurations. Just wanted to have a docker image ready to simulate various scenarios of OOM in clusters and docker environments.

## Usage

### Environment Variables

| Variable           | Description                                       | Default Value |
|--------------------|---------------------------------------------------|---------------|
| `ALLOC_CHUNKS_SZ`  | Size of each memory chunk in bytes               | -             |
| `ALLOC_CHUNKS_NB`  | Number of memory chunks to allocate               | 1             |
| `ALLOC_DELAY`      | Delay in milliseconds between each allocation     | 0             |
| `ALLOC_FINAL_DELAY`| Final delay in milliseconds after allocations    | 0             |

## Configuration Details

- `ALLOC_CHUNKS_SZ`: Must be set to a positive number.
- `ALLOC_CHUNKS_NB`: If set, must be a positive number.
- `ALLOC_DELAY`: If set, must be a non-zero positive number.
- `ALLOC_FINAL_DELAY`: If set, must be a non-zero positive number.

