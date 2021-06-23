
/* Copyright (c) 2021 Intel
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>
#include <linux/btf.h>

struct {
	__uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__type(key, u32);
	__type(value, long);
	__uint(max_entries, 256);
} packet_info SEC(".maps");

struct xdp_hints {
	u64 rx_timestamp;
};

struct xdp_hints___igc {
	u64 rx_timestamp;
	u64 yet_another_timestamp;
};

SEC("xdp_hints_hash")
int xdp_hints_hash_prog(struct xdp_md *ctx)
{
	struct xdp_hints *meta = (void *)(long)ctx->data_meta;
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	int rc = XDP_DROP;
	long *value;
	u32 key = 0;
	long size, meta_size, val;

	if (meta + 1 <= data) {
		value = bpf_map_lookup_elem(&packet_info, &key);
		if (value)
			*value = BPF_CORE_READ(meta, rx_timestamp);

		/* Just to show how access to specific driver hints would be */
		val = BPF_CORE_READ((struct xdp_hints___igc *)meta,
				yet_another_timestamp);
		bpf_printk("yet another timestamp %lu", val);
	}
	return rc;
}

char _license[] SEC("license") = "GPL";
