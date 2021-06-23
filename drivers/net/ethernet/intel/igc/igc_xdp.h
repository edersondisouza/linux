/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2020, Intel Corporation. */

#ifndef _IGC_XDP_H_
#define _IGC_XDP_H_

int igc_xdp_set_prog(struct igc_adapter *adapter, struct bpf_prog *prog,
		     struct netlink_ext_ack *extack, u32 flags);
int igc_xdp_setup_pool(struct igc_adapter *adapter, struct xsk_buff_pool *pool,
		       u16 queue_id);

static inline bool igc_xdp_is_enabled(struct igc_adapter *adapter)
{
	return !!adapter->xdp_prog;
}

struct xdp_meta_generic___igc {
	u64 tx_tstamp;
	u64 tstamp;
	u32 btf_id;
} __packed;

#endif /* _IGC_XDP_H_ */
