[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 5
  xmax = 0.01
  ymax = 0.01
  elem_type = QUAD8
[]

[Variables]
  [./u]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./phi]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    vars = a
    vals = 100
    value = t*y*sin(a*pi*x)
  [../]
  [./forcing_func]
    type = ParsedFunction
    vars = 'a Dv'
    vals = '100 0.00002178'
    value = 'y*sin(a*pi*x) + a*a*Dv*t*y*cos(a*pi*x)*pi + a*a*Dv*(1-a*x)*t*y*sin(a*pi*x)*pi*pi'
  [../]
  [./phi_func]
    type = ParsedFunction
    value = 200*x-1
  [../]
[]

[Kernels]
  [./u_diff]
    type = MatDiffusion
    variable = u
    block = 0
    D_name = diffusion_coefficient
  [../]
  [./mms]
    type = UserForcingFunction
    variable = u
    function = forcing_func
  [../]
  [./u_time]
    type = TimeDerivative
    variable = u
  [../]
[]

[AuxKernels]
  [./phi_aux]
    type = FunctionAux
    variable = phi
    function = phi_func
    execute_on = 'initial linear nonlinear'
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'bottom left right top'
    function = u_func
  [../]
[]

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
  [./hmax]
    type = AverageElementSize
    execute_on = 'initial timestep_end'
  [../]
  [./L2_norm]
    type = ElementL2Norm
    variable = u
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 5
  dt = 0.0001
  nl_rel_tol = 1e-12
[]

[Outputs]
  exodus = true
  csv = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
[]

[PikaMaterials]
  reference_temperature = 263.15
  phase = phi
  temperature = 268.15
  water_vapor_diffusion_coefficient = 0.00002178
[]
