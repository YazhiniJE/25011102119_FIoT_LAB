"""
Circuit Schematic Generator for IoT Lab Assessment Repo
Generates clean, standardized circuit.png diagrams using matplotlib.
"""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import os

# Wire colors
COLORS = {
    'gpio': '#1f77b4',   # Blue
    'uart': '#2ca02c',   # Green
    'i2c': '#9467bd',    # Purple
    'power': '#d62728',  # Red
    'gnd': '#111111'     # Black
}

def draw(path, title, board, mcu, peripherals, bottom_text=""):
    """
    Draw a clean, standardized schematic with MCU on left and peripherals on right.
    
    peripherals is a list of dicts:
    [
        {
            'name': 'LED (P1.0)',
            'pins': [('P1.0', 'Anode', 'gpio'), ('GND', 'Cathode', 'gnd'), ('VCC', 'VCC', 'power')]
        },
        ...
    ]
    """
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    
    # Calculate required height based on total connections
    total_conns = sum(len(p['pins']) for p in peripherals)
    fig_height = max(7, total_conns * 0.45 + 2.5)
    fig, ax = plt.subplots(figsize=(12, fig_height), dpi=130)
    
    ax.set_xlim(0, 12)
    ax.set_ylim(0, fig_height)
    ax.axis('off')
    
    # Background
    fig.patch.set_facecolor('white')
    ax.set_facecolor('white')
    
    # Title
    ax.text(6, fig_height - 0.6, title, fontsize=15, fontweight='bold', ha='center', va='center', color='#111827')
    
    # Layout coordinates
    mcu_x, mcu_w = 0.8, 3.2
    mcu_y_top = fig_height - 1.5
    mcu_y_bot = 1.2
    mcu_h = mcu_y_top - mcu_y_bot
    
    periph_x = 7.8
    periph_w = 3.4
    
    # Draw MCU Box
    mcu_box = patches.FancyBboxPatch((mcu_x, mcu_y_bot), mcu_w, mcu_h,
                                     boxstyle="round,pad=0.1,rounding_size=0.15",
                                     linewidth=2, edgecolor='#1e3a8a', facecolor='#eff6ff')
    ax.add_patch(mcu_box)
    
    # MCU Header
    ax.text(mcu_x + mcu_w / 2, mcu_y_top - 0.4, board, fontsize=12, fontweight='bold', ha='center', va='center', color='#1e3a8a')
    ax.text(mcu_x + mcu_w / 2, mcu_y_top - 0.75, f"MCU: {mcu}", fontsize=11, fontweight='semibold', ha='center', va='center', color='#1f2937')
    ax.plot([mcu_x + 0.2, mcu_x + mcu_w - 0.2], [mcu_y_top - 0.95, mcu_y_top - 0.95], color='#93c5fd', lw=1.5)
    
    # Compute wire positions
    wire_y_spacing = (mcu_h - 1.4) / (total_conns + 1)
    current_wire_idx = 0
    
    # Total height allocated for peripherals
    avail_h = mcu_h - 0.2
    n_p = len(peripherals)
    p_spacing = 0.4
    total_pins = total_conns
    
    # Peripheral boxes positioning
    periph_boxes = []
    curr_top = mcu_y_top - 0.2
    for p in peripherals:
        pins_count = len(p['pins'])
        # Height proportional to pins count with minimum
        box_h = max(1.1, pins_count * 0.45 + 0.5)
        box_y = curr_top - box_h
        periph_boxes.append((box_y, box_h))
        curr_top = box_y - p_spacing

    # Adjust scaling if needed
    if periph_boxes[-1][0] < mcu_y_bot:
        scale_ratio = (mcu_y_top - 0.2 - mcu_y_bot) / (mcu_y_top - 0.2 - periph_boxes[-1][0])
        curr_top = mcu_y_top - 0.2
        new_boxes = []
        for p in peripherals:
            pins_count = len(p['pins'])
            box_h = max(0.9, (pins_count * 0.45 + 0.5) * scale_ratio)
            box_y = curr_top - box_h
            new_boxes.append((box_y, box_h))
            curr_top = box_y - (p_spacing * scale_ratio)
        periph_boxes = new_boxes
    
    # Draw peripherals and connections
    all_connections = []
    
    for p_idx, p in enumerate(peripherals):
        box_y, box_h = periph_boxes[p_idx]
        p_box = patches.FancyBboxPatch((periph_x, box_y), periph_w, box_h,
                                       boxstyle="round,pad=0.1,rounding_size=0.15",
                                       linewidth=1.8, edgecolor='#047857', facecolor='#f0fdf4')
        ax.add_patch(p_box)
        
        # Peripheral Name
        ax.text(periph_x + periph_w / 2, box_y + box_h - 0.3, p['name'],
                fontsize=11, fontweight='bold', ha='center', va='center', color='#065f46')
        ax.plot([periph_x + 0.2, periph_x + periph_w - 0.2], [box_y + box_h - 0.45, box_y + box_h - 0.45],
                color='#a7f3d0', lw=1.2)
        
        pins = p['pins']
        pin_spacing = (box_h - 0.6) / (len(pins) + 1)
        
        for pin_idx, (mcu_pin, periph_pin, wire_type) in enumerate(pins):
            p_pin_y = box_y + box_h - 0.6 - (pin_idx + 1) * pin_spacing
            all_connections.append((mcu_pin, periph_pin, wire_type, p_pin_y))

    # Calculate balanced MCU pin Y positions
    n_conns = len(all_connections)
    mcu_conn_spacing = (mcu_h - 1.4) / (n_conns + 1)
    
    for i, (mcu_pin, periph_pin, wire_type, periph_pin_y) in enumerate(all_connections):
        mcu_pin_y = mcu_y_top - 1.2 - (i + 0.5) * mcu_conn_spacing
        color = COLORS.get(wire_type.lower(), '#1f77b4')
        
        # MCU Pin label & pin marker
        ax.plot([mcu_x + mcu_w], [mcu_pin_y], marker='o', markersize=5, color=color)
        ax.text(mcu_x + mcu_w - 0.15, mcu_pin_y, mcu_pin,
                fontsize=9.5, fontweight='semibold', ha='right', va='center', color='#111827')
        
        # Peripheral Pin label & pin marker
        ax.plot([periph_x], [periph_pin_y], marker='o', markersize=5, color=color)
        ax.text(periph_x + 0.15, periph_pin_y, periph_pin,
                fontsize=9.5, fontweight='semibold', ha='left', va='center', color='#111827')
        
        # Wire: straight line or gentle bezier
        mid_x1 = mcu_x + mcu_w + 0.8
        mid_x2 = periph_x - 0.8
        ax.plot([mcu_x + mcu_w, mid_x1, mid_x2, periph_x],
                [mcu_pin_y, mcu_pin_y, periph_pin_y, periph_pin_y],
                color=color, lw=2.0, alpha=0.9)
    
    # Bottom text
    if bottom_text:
        ax.text(6, 0.45, bottom_text, fontsize=10, ha='center', va='center',
                fontstyle='italic', color='#4b5563',
                bbox=dict(boxstyle="round,pad=0.4", facecolor='#f9fafb', edgecolor='#e5e7eb', lw=1))
    
    # Legend
    legend_elements = [
        patches.Patch(facecolor=COLORS['gpio'], edgecolor=COLORS['gpio'], label='GPIO Signal'),
        patches.Patch(facecolor=COLORS['uart'], edgecolor=COLORS['uart'], label='UART (TX/RX)'),
        patches.Patch(facecolor=COLORS['i2c'], edgecolor=COLORS['i2c'], label='I2C (SCL/SDA)'),
        patches.Patch(facecolor=COLORS['power'], edgecolor=COLORS['power'], label='Power (+5V / +3.3V)'),
        patches.Patch(facecolor=COLORS['gnd'], edgecolor=COLORS['gnd'], label='Ground (GND)')
    ]
    ax.legend(handles=legend_elements, loc='upper right', bbox_to_anchor=(0.98, 0.98),
              fontsize=8.5, framealpha=0.95, facecolor='white', edgecolor='#d1d5db', title="Wire Legend")
    
    plt.tight_layout()
    plt.savefig(path, dpi=130, facecolor=fig.get_facecolor(), edgecolor='none', bbox_inches='tight')
    plt.close()
    print(f"Generated schematic: {path}")

if __name__ == '__main__':
    # Test generation
    test_periphs = [
        {
            'name': 'LED 0 Indicator',
            'pins': [
                ('P1.0', 'Anode', 'gpio'),
                ('GND', 'Cathode (via 330Ω)', 'gnd')
            ]
        }
    ]
    draw('test_circuit.png', 'Continuous Assessment 2: Bare-Metal LED Blink',
         '8051 Development Kit', 'AT89S52', test_periphs,
         '11.0592 MHz Crystal | VCC (Pin 40) = +5V | GND (Pin 20) = 0V')

