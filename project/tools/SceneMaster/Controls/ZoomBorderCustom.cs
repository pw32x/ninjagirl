#region Assembly Wpf.Controls.PanAndZoom, Version=2.3.4.0, Culture=neutral, PublicKeyToken=null
// C:\Users\shawn\.nuget\packages\wpf.controls.panandzoom\2.3.4\lib\netcoreapp3.1\Wpf.Controls.PanAndZoom.dll
// Decompiled with ICSharpCode.Decompiler 8.1.1.7464
#endregion

using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using PanAndZoom;
using Wpf.MatrixExtensions;

#nullable enable

namespace SceneMaster.Controls;

//
// Summary:
//     Pan and zoom control for WPF.
public class ZoomBorderCustom : Border, IPanAndZoom
{
    private UIElement? _element;

    private Point _pan;

    private Point _previous;

    private Matrix _matrix;

    private bool _isPanning;

    private static readonly StretchMode[] s_autoFitModes = (StretchMode[])Enum.GetValues(typeof(StretchMode));

    private static readonly ButtonName[] s_buttonNames = (ButtonName[])Enum.GetValues(typeof(ButtonName));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.PanButton dependency property.
    public static readonly DependencyProperty PanButtonProperty = DependencyProperty.Register("PanButton", typeof(ButtonName), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(ButtonName.Left, FrameworkPropertyMetadataOptions.None));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.ZoomSpeed dependency property.
    public static readonly DependencyProperty ZoomSpeedProperty = DependencyProperty.Register("ZoomSpeed", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(1.2, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.Stretch dependency property.
    public static readonly DependencyProperty StretchProperty = DependencyProperty.Register("Stretch", typeof(StretchMode), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(StretchMode.Uniform, FrameworkPropertyMetadataOptions.AffectsArrange));

    internal static readonly DependencyPropertyKey ZoomXPropertyKey = DependencyProperty.RegisterReadOnly("ZoomX", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(1.0, FrameworkPropertyMetadataOptions.None));

    internal static readonly DependencyPropertyKey ZoomYPropertyKey = DependencyProperty.RegisterReadOnly("ZoomY", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(1.0, FrameworkPropertyMetadataOptions.None));

    internal static readonly DependencyPropertyKey OffsetXPropertyKey = DependencyProperty.RegisterReadOnly("OffsetX", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.None));

    internal static readonly DependencyPropertyKey OffsetYPropertyKey = DependencyProperty.RegisterReadOnly("OffsetY", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.None));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.ZoomX dependency property.
    public static readonly DependencyProperty ZoomXProperty = ZoomXPropertyKey.DependencyProperty;

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.ZoomY dependency property.
    public static readonly DependencyProperty ZoomYProperty = ZoomYPropertyKey.DependencyProperty;

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.OffsetX dependency property.
    public static readonly DependencyProperty OffsetXProperty = OffsetXPropertyKey.DependencyProperty;

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.OffsetY dependency property.
    public static readonly DependencyProperty OffsetYProperty = OffsetYPropertyKey.DependencyProperty;

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.EnableConstrains dependency
    //     property.
    public static readonly DependencyProperty EnableConstrainsProperty = DependencyProperty.Register("EnableConstrains", typeof(bool), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(true, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MinZoomX dependency property.
    public static readonly DependencyProperty MinZoomXProperty = DependencyProperty.Register("MinZoomX", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.NegativeInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MaxZoomX dependency property.
    public static readonly DependencyProperty MaxZoomXProperty = DependencyProperty.Register("MaxZoomX", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.PositiveInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MinZoomY dependency property.
    public static readonly DependencyProperty MinZoomYProperty = DependencyProperty.Register("MinZoomY", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.NegativeInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MaxZoomY dependency property.
    public static readonly DependencyProperty MaxZoomYProperty = DependencyProperty.Register("MaxZoomY", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.PositiveInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MinOffsetX dependency property.
    public static readonly DependencyProperty MinOffsetXProperty = DependencyProperty.Register("MinOffsetX", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.NegativeInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MaxOffsetX dependency property.
    public static readonly DependencyProperty MaxOffsetXProperty = DependencyProperty.Register("MaxOffsetX", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.PositiveInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MinOffsetY dependency property.
    public static readonly DependencyProperty MinOffsetYProperty = DependencyProperty.Register("MinOffsetY", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.NegativeInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.MaxOffsetY dependency property.
    public static readonly DependencyProperty MaxOffsetYProperty = DependencyProperty.Register("MaxOffsetY", typeof(double), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(double.PositiveInfinity, FrameworkPropertyMetadataOptions.AffectsMeasure));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.EnableInput dependency property.
    public static readonly DependencyProperty EnableInputProperty = DependencyProperty.Register("EnableInput", typeof(bool), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(true));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.EnableGestureZoom dependency
    //     property.
    public static readonly DependencyProperty EnableGestureZoomProperty = DependencyProperty.Register("EnableGestureZoom", typeof(bool), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(true));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.EnableGestureRotation dependency
    //     property.
    public static readonly DependencyProperty EnableGestureRotationProperty = DependencyProperty.Register("EnableGestureRotation", typeof(bool), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(true));

    //
    // Summary:
    //     Identifies the Wpf.Controls.PanAndZoom.ZoomBorder.EnableGestureTranslation dependency
    //     property.
    public static readonly DependencyProperty EnableGestureTranslationProperty = DependencyProperty.Register("EnableGestureTranslation", typeof(bool), typeof(ZoomBorderCustom), new FrameworkPropertyMetadata(true));

    //
    // Summary:
    //     Gets available stretch modes.
    public static StretchMode[] StretchModes => s_autoFitModes;

    //
    // Summary:
    //     Gets available button names.
    public static ButtonName[] ButtonNames => s_buttonNames;

    public Action<double, double, double, double>? InvalidatedChild { get; set; }

    public ButtonName PanButton
    {
        get
        {
            return (ButtonName)GetValue(PanButtonProperty);
        }
        set
        {
            SetValue(PanButtonProperty, value);
        }
    }

    public double ZoomSpeed
    {
        get
        {
            return (double)GetValue(ZoomSpeedProperty);
        }
        set
        {
            SetValue(ZoomSpeedProperty, value);
        }
    }

    public StretchMode Stretch
    {
        get
        {
            return (StretchMode)GetValue(StretchProperty);
        }
        set
        {
            SetValue(StretchProperty, value);
        }
    }

    public double ZoomX => (double)GetValue(ZoomXProperty);

    public double ZoomY => (double)GetValue(ZoomYProperty);

    public double OffsetX => (double)GetValue(OffsetXProperty);

    public double OffsetY => (double)GetValue(OffsetYProperty);

    public bool EnableConstrains
    {
        get
        {
            return (bool)GetValue(EnableConstrainsProperty);
        }
        set
        {
            SetValue(EnableConstrainsProperty, value);
        }
    }

    public double MinZoomX
    {
        get
        {
            return (double)GetValue(MinZoomXProperty);
        }
        set
        {
            SetValue(MinZoomXProperty, value);
        }
    }

    public double MaxZoomX
    {
        get
        {
            return (double)GetValue(MaxZoomXProperty);
        }
        set
        {
            SetValue(MaxZoomXProperty, value);
        }
    }

    public double MinZoomY
    {
        get
        {
            return (double)GetValue(MinZoomYProperty);
        }
        set
        {
            SetValue(MinZoomYProperty, value);
        }
    }

    public double MaxZoomY
    {
        get
        {
            return (double)GetValue(MaxZoomYProperty);
        }
        set
        {
            SetValue(MaxZoomYProperty, value);
        }
    }

    public double MinOffsetX
    {
        get
        {
            return (double)GetValue(MinOffsetXProperty);
        }
        set
        {
            SetValue(MinOffsetXProperty, value);
        }
    }

    public double MaxOffsetX
    {
        get
        {
            return (double)GetValue(MaxOffsetXProperty);
        }
        set
        {
            SetValue(MaxOffsetXProperty, value);
        }
    }

    public double MinOffsetY
    {
        get
        {
            return (double)GetValue(MinOffsetYProperty);
        }
        set
        {
            SetValue(MinOffsetYProperty, value);
        }
    }

    public double MaxOffsetY
    {
        get
        {
            return (double)GetValue(MaxOffsetYProperty);
        }
        set
        {
            SetValue(MaxOffsetYProperty, value);
        }
    }

    public bool EnableInput
    {
        get
        {
            return (bool)GetValue(EnableInputProperty);
        }
        set
        {
            SetValue(EnableInputProperty, value);
        }
    }

    public bool EnableGestureZoom
    {
        get
        {
            return (bool)GetValue(EnableGestureZoomProperty);
        }
        set
        {
            SetValue(EnableGestureZoomProperty, value);
        }
    }

    public bool EnableGestureRotation
    {
        get
        {
            return (bool)GetValue(EnableGestureRotationProperty);
        }
        set
        {
            SetValue(EnableGestureRotationProperty, value);
        }
    }

    public bool EnableGestureTranslation
    {
        get
        {
            return (bool)GetValue(EnableGestureTranslationProperty);
        }
        set
        {
            SetValue(EnableGestureTranslationProperty, value);
        }
    }

    //
    // Summary:
    //     Gets or sets single child of a Wpf.Controls.PanAndZoom.ZoomBorder control.
    public override UIElement Child
    {
        get
        {
            return base.Child;
        }
        set
        {
            base.Child = value;
            ChildChanged(value);
        }
    }

    //
    // Summary:
    //     Initializes a new instance of the Wpf.Controls.PanAndZoom.ZoomBorder class.
    public ZoomBorderCustom()
    {
        Defaults();
        base.Focusable = true;
        base.Background = Brushes.Transparent;
        base.Loaded += PanAndZoom_Loaded;
        base.Unloaded += PanAndZoom_Unloaded;
        base.IsManipulationEnabled = true;
    }

    private void Defaults()
    {
        _isPanning = false;
        _matrix = Matrix.Identity;
    }

    //
    // Summary:
    //     Arranges the control's child.
    //
    // Parameters:
    //   finalSize:
    //     The size allocated to the control.
    //
    // Returns:
    //     The space taken.
    protected override Size ArrangeOverride(Size finalSize)
    {
        Size result = base.ArrangeOverride(finalSize);
        if (_element == null || !_element.IsMeasureValid)
        {
            return result;
        }

        AutoFit(result.Width, result.Height, _element.RenderSize.Width, _element.RenderSize.Height);
        return result;
    }

    private void PanAndZoom_Loaded(object sender, RoutedEventArgs e)
    {
        ChildChanged(base.Child);
    }

    private void PanAndZoom_Unloaded(object sender, RoutedEventArgs e)
    {
        DetachElement();
    }

    private void Border_PreviewMouseWheel(object sender, MouseWheelEventArgs e)
    {
        if (EnableInput)
        {
            Wheel(e);
        }
    }

    private void Border_PreviewMouseDown(object sender, MouseButtonEventArgs e)
    {
        if (EnableInput)
        {
            ButtonName panButton = PanButton;
            if ((e.ChangedButton == MouseButton.Left && panButton == ButtonName.Left) || (e.ChangedButton == MouseButton.Right && panButton == ButtonName.Right) || (e.ChangedButton == MouseButton.Middle && panButton == ButtonName.Middle))
            {
                Pressed(e);
            }
        }
    }

    private void Border_PreviewMouseUp(object sender, MouseButtonEventArgs e)
    {
        if (EnableInput)
        {
            ButtonName panButton = PanButton;
            if ((e.ChangedButton == MouseButton.Left && panButton == ButtonName.Left) || (e.ChangedButton == MouseButton.Right && panButton == ButtonName.Right) || (e.ChangedButton == MouseButton.Middle && panButton == ButtonName.Middle))
            {
                Released(e);
            }
        }
    }

    private void Border_PreviewMouseMove(object sender, MouseEventArgs e)
    {
        if (EnableInput)
        {
            Moved(e);
        }
    }

    private void Border_ManipulationStarting(object? sender, ManipulationStartingEventArgs e)
    {
        if (EnableInput && _element != null)
        {
            e.ManipulationContainer = this;
        }
    }

    private void Border_ManipulationDelta(object? sender, ManipulationDeltaEventArgs e)
    {
        if (EnableInput && _element != null)
        {
            Manipulation(e.DeltaManipulation);
            e.Handled = true;
        }
    }

    private void ChildChanged(UIElement element)
    {
        if (element != null && element != _element && _element != null)
        {
            DetachElement();
        }

        if (element != null && element != _element)
        {
            AttachElement(element);
        }
    }

    private void AttachElement(UIElement element)
    {
        if (element != null)
        {
            Defaults();
            _element = element;
            Focus();
            base.PreviewMouseWheel += Border_PreviewMouseWheel;
            base.PreviewMouseDown += Border_PreviewMouseDown;
            base.PreviewMouseUp += Border_PreviewMouseUp;
            base.PreviewMouseMove += Border_PreviewMouseMove;
            base.ManipulationStarting += Border_ManipulationStarting;
            base.ManipulationDelta += Border_ManipulationDelta;
        }
    }

    private void DetachElement()
    {
        if (_element != null)
        {
            base.PreviewMouseWheel -= Border_PreviewMouseWheel;
            base.PreviewMouseDown -= Border_PreviewMouseDown;
            base.PreviewMouseUp -= Border_PreviewMouseUp;
            base.PreviewMouseMove -= Border_PreviewMouseMove;
            base.ManipulationStarting -= Border_ManipulationStarting;
            base.ManipulationDelta -= Border_ManipulationDelta;
            _element.RenderTransform = null;
            _element = null;
            Defaults();
        }
    }

    private void Wheel(MouseWheelEventArgs e)
    {
        if (_element != null && Mouse.Captured == null)
        {
            Point position = e.GetPosition(_element);
            ZoomDeltaTo(e.Delta, position.X, position.Y);
        }
    }

    private void Pressed(MouseButtonEventArgs e)
    {
        if (_element != null && Mouse.Captured == null && !_isPanning)
        {
            Point position = e.GetPosition(_element);
            StartPan(position.X, position.Y);
            _element.CaptureMouse();
            _isPanning = true;
        }
    }

    private void Released(MouseButtonEventArgs e)
    {
        if (_element != null && _element.IsMouseCaptured && _isPanning)
        {
            _element.ReleaseMouseCapture();
            _isPanning = false;
        }
    }

    private void Moved(MouseEventArgs e)
    {
        if (_element != null && _element.IsMouseCaptured && _isPanning)
        {
            Point position = e.GetPosition(_element);
            PanTo(position.X, position.Y);
        }
    }

    private void Manipulation(ManipulationDelta delta)
    {
        if (_element != null)
        {
            double num = (delta.Scale.X - 1.0) * ZoomSpeed + 1.0;
            Point point = new Point(_element.RenderSize.Width / 2.0, _element.RenderSize.Height / 2.0);
            point = _matrix.Transform(point);
            if (EnableGestureZoom)
            {
                _matrix.ScaleAt(num, num, point.X, point.Y);
            }

            if (EnableGestureRotation)
            {
                _matrix.RotateAt(delta.Rotation, point.X, point.Y);
            }

            if (EnableGestureTranslation)
            {
                _matrix.Translate(delta.Translation.X, delta.Translation.Y);
            }

            Invalidate();
        }
    }

    private double Constrain(double value, double minimum, double maximum)
    {
        if (minimum > maximum)
        {
            throw new ArgumentException("Parameter minimum is greater than maximum.");
        }

        if (maximum < minimum)
        {
            throw new ArgumentException("Parameter maximum is lower than minimum.");
        }

        return Math.Min(Math.Max(value, minimum), maximum);
    }

    private void Constrain()
    {
        double m = Constrain(_matrix.M11, MinZoomX, MaxZoomX);
        double m2 = Constrain(_matrix.M22, MinZoomY, MaxZoomY);
        double offsetX = Constrain(_matrix.OffsetX, MinOffsetX, MaxOffsetX);
        double offsetY = Constrain(_matrix.OffsetY, MinOffsetY, MaxOffsetY);
        _matrix = new Matrix(m, 0.0, 0.0, m2, offsetX, offsetY);
    }

    public void Invalidate()
    {
        if (_element != null)
        {
            if (EnableConstrains)
            {
                Constrain();
            }

            SetValue(ZoomXPropertyKey, _matrix.M11);
            SetValue(ZoomYPropertyKey, _matrix.M22);
            SetValue(OffsetXPropertyKey, _matrix.OffsetX);
            SetValue(OffsetYPropertyKey, _matrix.OffsetY);
            InvalidatedChild?.Invoke(_matrix.M11, _matrix.M22, _matrix.OffsetX, _matrix.OffsetY);
            _element.RenderTransformOrigin = new Point(0.0, 0.0);
            _element.RenderTransform = new MatrixTransform(_matrix);
            _element.InvalidateVisual();
        }
    }

    public void ZoomTo(double zoom, double x, double y)
    {
        _matrix = MatrixHelper.ScaleAtPrepend(_matrix, zoom, zoom, x, y);
        Invalidate();
    }

    public void ZoomDeltaTo(double delta, double x, double y)
    {
        ZoomTo((delta > 0.0) ? ZoomSpeed : (1.0 / ZoomSpeed), x, y);
    }

    public void StartPan(double x, double y)
    {
        _pan = default(Point);
        _previous = new Point(x, y);
    }

    public void PanTo(double x, double y)
    {
        double x2 = x - _previous.X;
        double y2 = y - _previous.Y;
        Point point = new Point(x2, y2);
        _previous = new Point(x, y);
        _pan = new Point(_pan.X + point.X, _pan.Y + point.Y);
        _matrix = MatrixHelper.TranslatePrepend(_matrix, _pan.X, _pan.Y);
        Invalidate();
    }

    private Matrix GetMatrix(double panelWidth, double panelHeight, double elementWidth, double elementHeight, StretchMode mode)
    {
        double num = panelWidth / elementWidth;
        double num2 = panelHeight / elementHeight;
        double centerX = ((elementWidth < panelWidth) ? (elementWidth / 2.0) : 0.0);
        double centerY = ((elementHeight < panelHeight) ? (elementHeight / 2.0) : 0.0);
        double num3 = 1.0;
        switch (mode)
        {
            case StretchMode.Fill:
                if (elementWidth > panelWidth && elementHeight > panelHeight)
                {
                    centerX = (panelWidth - elementWidth * num) / 2.0;
                    centerY = (panelHeight - elementHeight * num2) / 2.0;
                    Matrix result3 = MatrixHelper.ScaleAt(num, num2, 0.0, 0.0);
                    result3.OffsetX = centerX;
                    result3.OffsetY = centerY;
                    return result3;
                }

                return MatrixHelper.ScaleAt(num, num2, centerX, centerY);
            case StretchMode.Uniform:
                num3 = Math.Min(num, num2);
                if (elementWidth > panelWidth && elementHeight > panelHeight)
                {
                    centerX = (panelWidth - elementWidth * num3) / 2.0;
                    centerY = (panelHeight - elementHeight * num3) / 2.0;
                    Matrix result2 = MatrixHelper.ScaleAt(num3, num3, 0.0, 0.0);
                    result2.OffsetX = centerX;
                    result2.OffsetY = centerY;
                    return result2;
                }

                return MatrixHelper.ScaleAt(num3, num3, centerX, centerY);
            case StretchMode.UniformToFill:
                num3 = Math.Max(num, num2);
                if (elementWidth > panelWidth && elementHeight > panelHeight)
                {
                    centerX = (panelWidth - elementWidth * num3) / 2.0;
                    centerY = (panelHeight - elementHeight * num3) / 2.0;
                    Matrix result = MatrixHelper.ScaleAt(num3, num3, 0.0, 0.0);
                    result.OffsetX = centerX;
                    result.OffsetY = centerY;
                    return result;
                }

                return MatrixHelper.ScaleAt(num3, num3, centerX, centerY);
            default:
                return Matrix.Identity;
        }
    }

    public void Fill(double panelWidth, double panelHeight, double elementWidth, double elementHeight)
    {
        if (_element != null)
        {
            _matrix = GetMatrix(panelWidth, panelHeight, elementWidth, elementHeight, StretchMode.Fill);
            Invalidate();
        }
    }

    public void Uniform(double panelWidth, double panelHeight, double elementWidth, double elementHeight)
    {
        if (_element != null)
        {
            _matrix = GetMatrix(panelWidth, panelHeight, elementWidth, elementHeight, StretchMode.Uniform);
            Invalidate();
        }
    }

    public void UniformToFill(double panelWidth, double panelHeight, double elementWidth, double elementHeight)
    {
        if (_element != null)
        {
            _matrix = GetMatrix(panelWidth, panelHeight, elementWidth, elementHeight, StretchMode.UniformToFill);
            Invalidate();
        }
    }

    public void AutoFit(double panelWidth, double panelHeight, double elementWidth, double elementHeight)
    {
        if (_element != null)
        {
            switch (Stretch)
            {
                case StretchMode.Fill:
                    Fill(panelWidth, panelHeight, elementWidth, elementHeight);
                    break;
                case StretchMode.Uniform:
                    Uniform(panelWidth, panelHeight, elementWidth, elementHeight);
                    break;
                case StretchMode.UniformToFill:
                    UniformToFill(panelWidth, panelHeight, elementWidth, elementHeight);
                    break;
            }

            Invalidate();
        }
    }

    public void ToggleStretchMode()
    {
        switch (Stretch)
        {
            case StretchMode.None:
                Stretch = StretchMode.Fill;
                break;
            case StretchMode.Fill:
                Stretch = StretchMode.Uniform;
                break;
            case StretchMode.Uniform:
                Stretch = StretchMode.UniformToFill;
                break;
            case StretchMode.UniformToFill:
                Stretch = StretchMode.None;
                break;
        }
    }

    public void Reset()
    {
        _matrix = Matrix.Identity;
        Invalidate();
    }

    public void Fill()
    {
        if (_element != null)
        {
            Fill(base.RenderSize.Width, base.RenderSize.Height, _element.RenderSize.Width, _element.RenderSize.Height);
        }
    }

    public void Uniform()
    {
        if (_element != null)
        {
            Uniform(base.RenderSize.Width, base.RenderSize.Height, _element.RenderSize.Width, _element.RenderSize.Height);
        }
    }

    public void UniformToFill()
    {
        if (_element != null)
        {
            UniformToFill(base.RenderSize.Width, base.RenderSize.Height, _element.RenderSize.Width, _element.RenderSize.Height);
        }
    }

    public void AutoFit()
    {
        if (_element != null)
        {
            AutoFit(base.RenderSize.Width, base.RenderSize.Height, _element.RenderSize.Width, _element.RenderSize.Height);
        }
    }
}