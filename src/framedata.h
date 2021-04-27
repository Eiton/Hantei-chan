#ifndef FRAMEDATA_H_GUARD
#define FRAMEDATA_H_GUARD

#include <string>

struct Hitbox {
	short x1, y1, x2, y2;
};

struct Frame_AF {
	// rendering data
	bool		active;

	int		frame;
	int		frame_unk;

	int		offset_y;
	int		offset_x;

	int		duration;
	int		AFF;

	int		blend_mode;

	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	float		z_rotation;
	float		y_rotation;
	float		x_rotation;

	bool		has_zoom;
	float		zoom_x;
	float		zoom_y;

	int		AFJP;
};

struct Frame_AS {
	// state data
	int		speed_flags;
	int		speed_horz;
	int		speed_vert;
	int		accel_horz;
	int		accel_vert;

	int		ASMV;

	int		stand_state;

	int		cancel_flags;
};

struct Frame_AT {
	bool		active;

	int		guard_flags;

	int		proration;
	int		proration_type;

	int		damage;
	int		red_damage;
	int		dmg_unknown;
	int		circuit_gain;
};

struct Frame_EF {
	int		command;
	int		parameter;
	int		values[12];
};

struct Frame_IF {
	int		command;
	int		values[12];
};

struct Frame {
	Frame_AF	AF;

	Frame_AS	*AS;
	Frame_AT	*AT;

	Frame_EF	*EF[8];
	Frame_IF	*IF[8];

	Hitbox	*hitboxes[33];
};

struct Sequence {
	// sequence property data
	std::string	name;

	bool		is_move;
	std::string	move_name;
	int		move_meter;

	int		subframe_count;

	bool		initialized;

	char		*data;

	Frame	*frames;
	unsigned int	nframes;

	Hitbox	*hitboxes;
	unsigned int	nhitboxes;

	Frame_AT	*AT;
	unsigned int	nAT;

	Frame_AS	*AS;
	unsigned int	nAS;

	Frame_EF	*EF;
	unsigned int	nEF;

	Frame_IF	*IF;
	unsigned int	nIF;
};

class FrameData {
private:
	unsigned int	m_nsequences;

	bool		m_loaded;
public:

	Sequence	**m_sequences;
	bool		load(const char *filename);

	//Probably unnecessary.
	//bool load_move_list(Pack *pack, const char *filename);

	int get_sequence_count();

	Sequence *get_sequence(int n);
	std::string GetDecoratedName(int n);

	void free();

		FrameData();
		~FrameData();
};


#endif /* FRAMEDATA_H_GUARD */