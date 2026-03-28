# Data-Structures-Speed-Comparison

Porównanie wydajności tablicy dynamicznej i listy wiązanej w C++.

## Wyniki benchmarku

### Małe (N = 10 000)

| Operacja          | DynamicArray (ms) | LinkedList (ms) |
|-------------------|-------------------|-----------------|
| add_End           | 0.087             | 202.178         |
| add_Start         | 100.681           | 482.317         |
| add_Index(mid)    | 48.263            | 594.491         |
| find (worst)      | 17.899            | 39.462          |
| remove_End        | 0.033             | 477.038         |
| remove_Start      | 105.573           | 315.248         |
| remove_Index(mid) | 52.930            | 410.814         |

### Średnie (N = 100 000)

| Operacja          | DynamicArray (ms) | LinkedList (ms) |
|-------------------|-------------------|-----------------|
| add_End           | 0.859             | 20646.1         |
| add_Start         | 9440.92           | 1991.79         |
| add_Index(mid)    | 4727.89           | 16233.6         |
| find (worst)      | 174.615           | 414.303         |
| remove_End        | 0.347             | 27409.2         |
| remove_Start      | 10301.5           | 7427.32         |
| remove_Index(mid) | 5161.07           | 16090.1         |

## Wnioski

- **add_End / remove_End** — DynamicArray dominuje (O(1)), LinkedList cierpi na O(n²) przy N operacjach
- **add_Start / remove_Start** — LinkedList wygrywa przy dużych N (O(1) vs O(n))
- **find** — DynamicArray szybszy dzięki cache-friendly dostępowi do pamięci
- **add_Index / remove_Index (środek)** — obie struktury wolne (O(n)), LinkedList dodatkowo traci na traversalu wskaźników