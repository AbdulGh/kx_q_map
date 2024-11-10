.pq.so: hsym `libp.q;
.pq.make: 2:[.pq.so; (`make; 1)];
.pq.add: 2:[.pq.so; (`add; 3)];
.pq.front: 2:[.pq.so; (`front; 1)];
.pq.pop: 2:[.pq.so; (`pop; 1)];
.pq.size: 2:[.pq.so; (`size; 1)];

.pq.run_test: {
  my_map: .pq.make[];
  my_keys: 50 ? til 500;
  my_values: {x * x} each my_keys;
  {[my_map; pair] .pq.add[my_map] . pair }[my_map] each flip (my_keys; my_values);

  if [.pq.size[my_map] <> count my_keys; 'initial];

  last_kv: .pq.pop[my_map];
  popped: 1;
  while [0 < .pq.size[my_map];
    new_kv: .pq.pop[my_map];
    if [new_kv[0] < last_kv[0]; 'order];
    if [new_kv[1] <> new_kv[0] * new_kv[0]; 'value];
    last_kv: new_kv;
    popped +: 1;
    ];

  if [count <> count my_keys; 'size];

  -1 "Test successful!";
  }

.pq.run_test[];
